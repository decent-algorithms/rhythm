type fastGetLast('ds, 'el) =
  | SlowGetLast
  | GetLastExn('ds => 'el);

type fastAddLast('ds, 'el) =
  | SlowAddLast
  | AddLast(('el, 'ds) => 'ds);

type fastRemoveLast('ds, 'el) =
  | SlowRemoveLast
  | RemoveLastExn('ds => 'ds);

module type Config = {
  type t('el);

  let toList: t('el) => list('el);
  let fromList: list('el) => t('el);

  let isEmpty: t('el) => bool;
  let fastGetLast: fastGetLast(t('el), 'el);
  let fastAddLast: fastAddLast(t('el), 'el);
  let fastRemoveLast: fastRemoveLast(t('el), 'el);
};

module Default = {
  let fastGetLast = SlowGetLast;
  let fastAddLast = SlowAddLast;
  let fastRemoveLast = SlowRemoveLast;
};

module type Interface = {
  type tBack('el);

  /**
`getLast(ds)` returns an option containing the last element of the data
structure `ds` if it exists, `None` otherwise.

```
getLast([1, 2, 3, 4])  // Some(4)
getLast([])            // None
```
   */
  let getLast: tBack('el) => option('el);

  /**
`getLastExn(ds)` returns the last element of the data structure `ds` if it
exists, raises an exception otherwise.

```
getLastExn([1, 2, 3, 4])  // 4
getLastExn([])            // raises exception
```
   */
  let getLastExn: tBack('el) => 'el;

  /**
`getLastN(n, ds)` returns an option containing the last `n` elements of the
data structure `ds` if they exist, `None` otherwise.

```
getLastN(2, [1, 2, 3, 4])  // Some([3, 4])
getLastN(1, [1, 2, 3, 4])  // Some([4])
getLastN(0, [])            // Some([])
getLastN(1000, [1, 2])     // None
getLastN(1, [])            // None
```
   */
  let getLastN: (int, tBack('el)) => option(tBack('el));

  /**
`getLastNExn(n, ds)` returns the last `n` elements of the data structure `ds`
if they exist, raises an exception otherwise.

```
getLastNExn(2, [1, 2, 3, 4])  // [3, 4]
getLastNExn(1, [1, 2, 3, 4])  // [4]
getLastNExn(0, [])            // []
getLastNExn(1000, [1, 2])     // raises exception
getLastNExn(1, [])            // raises exception
```
   */
  let getLastNExn: (int, tBack('el)) => tBack('el);

  /**
`addLast(el, ds)` returns a new data structure with `el` added as the last
element of the given data structure `ds`.

```
addLast(9, [1, 2, 3])  // [1, 2, 3, 9]
addLast(9, [])         // [9]
```
   */
  let addLast: ('el, tBack('el)) => tBack('el);

  /**
`removeLast(ds)` returns an option containing a new data structure with the last
element of the given data structure `ds` removed if it exists, None otherwise.

__Note: Use `getLast` to access the last element if needed.__

```
removeLast([1, 2, 3])  // Some([1, 2])
removeLast([])         // None
```
   */
  let removeLast: tBack('el) => option(tBack('el));

  /**
`removeLastExn(ds)` returns a new data structure with the last element of the
given data structure `ds` removed if it exists, raises an exception otherwise.

__Note: Use `getLast` to access the last element if needed.__

```
removeLastExn([1, 2, 3])  // [1, 2]
removeLastExn([])         // raises exception
```
   */
  let removeLastExn: tBack('el) => tBack('el);

  /**
`removeLastN(n, ds)` returns an option containing a new data structure with the
last `n` elements of the given data structure `ds` removed if they exist, None
otherwise.

__Note: Use `getLastN` to access the last elements if needed.__

```
removeLastN(1, [1, 2, 3])     // Some([1, 2])
removeLastN(2, [1, 2, 3])     // Some([1])
removeLastN(0, [])            // Some([])
removeLastN(1000, [1, 2, 3])  // None
removeLastN(1, [])            // None

```
   */
  let removeLastN: (int, tBack('el)) => option(tBack('el));

  /**
`removeLastNExn(n, ds)` returns a new data structure with the last `n` elements of
the given data structure `ds` removed if they exist, raises an exception
otherwise.

__Note: Use `getLastN` to access the last elements if needed.__

```
removeLastNExn(1, [1, 2, 3])     // [1, 2]
removeLastNExn(2, [1, 2, 3])     // [1]
removeLastNExn(0, [])            // []
removeLastNExn(1000, [1, 2, 3])  // raises exception
removeLastNExn(1, [])            // raises exception

```
   */
  let removeLastNExn: (int, tBack('el)) => tBack('el);

  /**
`updateLast(fn, ds)` returns an option containing a new data structure with the
last element of the given data structure `ds` updated by `fn` if it exists,
None otherwise.

```
updateLast(x => x + 1, [1, 2, 3])  // Some([1, 2, 4])
updateLast(x => x + 1, [])         // None
```
   */
  let updateLast: ('el => 'el, tBack('el)) => option(tBack('el));

  /**
`updateLastExn(fn, ds)` returns a new data structure with the last element of
the given data structure `ds` updated by `fn` if it exists, raises an exception
otherwise.

```
updateLastExn(x => x + 1, [1, 2, 3])  // [1, 2, 4]
updateLastExn(x => x + 1, [])         // raises exception
```
   */
  let updateLastExn: ('el => 'el, tBack('el)) => tBack('el);
};

module Add =
       (Config: Config)
       : (Interface with type tBack('el) = Config.t('el)) => {
  type tBack('el) = Config.t('el);

  let getLastExn =
    switch (Config.fastGetLast) {
    | GetLastExn(getLastExn) => getLastExn
    | _ => (
        ds => ds |> Config.toList |> Caml.List.rev |> CamlListCore.getFirstExn
      )
    };

  let getLast = ds =>
    try (Some(getLastExn(ds))) {
    | _ => None
    };

  let getLastNExn =
    switch (Config.fastGetLast, Config.fastRemoveLast) {
    | (GetLastExn(getLastExn), RemoveLastExn(removeLastExn)) => (
        (count, ds) => {
          let ds = ref(ds);
          let result = ref([]);
          for (i in 0 to count - 1) {
            result := [getLastExn(ds^), ...result^];
            ds := removeLastExn(ds^);
          };
          result^ |> Config.fromList;
        }
      )
    | _ => (
        (count, ds) => {
          let list = ds |> Config.toList |> Caml.List.rev;
          let list = ref(list);
          let result = ref([]);
          for (i in 0 to count - 1) {
            result := [CamlListCore.getFirstExn(list^), ...result^];
            list := CamlListCore.dropFirstExn(list^);
          };
          result^ |> Config.fromList;
        }
      )
    };

  let getLastN = (count, ds) =>
    try (Some(getLastNExn(count, ds))) {
    | _ => None
    };

  let addLast =
    switch (Config.fastAddLast) {
    | AddLast(addLast) => addLast
    | _ => (
        (el, ds) => {
          let list = Config.toList(ds);
          let list = list @ [el];
          Config.fromList(list);
        }
      )
    };

  let removeLastExn =
    switch (Config.fastRemoveLast) {
    | RemoveLastExn(removeLastExn) => removeLastExn
    | _ => (
        ds => {
          let list = Config.toList(ds);
          let list = Caml.List.rev(list);
          let list =
            switch (list) {
            | [] => raise(Exceptions.Empty("FeatureBack.removeLastExn"))
            | [_, ...rest] => rest
            };
          list |> Caml.List.rev |> Config.fromList;
        }
      )
    };

  let removeLastNExn =
    switch (Config.fastRemoveLast) {
    | RemoveLastExn(removeLastExn) => (
        (count, ds) => {
          let ds = ref(ds);
          for (i in 0 to count - 1) {
            ds := removeLastExn(ds^);
          };
          ds^;
        }
      )
    | _ => (
        (count, ds) => {
          let list = Config.toList(ds);
          let list = Caml.List.rev(list);
          let list = ref(list);
          for (i in 0 to count - 1) {
            list := CamlListCore.dropFirstExn(list^);
          };
          list^ |> Caml.List.rev |> Config.fromList;
        }
      )
    };

  let removeLastN = (count, ds) =>
    try (Some(removeLastNExn(count, ds))) {
    | _ => None
    };

  let removeLast = ds =>
    try (Some(removeLastExn(ds))) {
    | _ => None
    };

  let updateLastExn =
    switch (Config.fastGetLast, Config.fastAddLast, Config.fastRemoveLast) {
    | (
        GetLastExn(getLastExn),
        AddLast(addLast),
        RemoveLastExn(removeLastExn),
      ) => (
        (fn, ds) =>
          if (Config.isEmpty(ds)) {
            raise(Exceptions.Empty("FeatureBack.updateLastExn"));
          } else {
            let first = getLastExn(ds);
            let rest = removeLastExn(ds);
            let newLast = fn(first);
            addLast(newLast, rest);
          }
      )
    | _ => (
        (fn, ds) => {
          let list = Config.toList(ds);
          let list = Caml.List.rev(list);
          let list =
            switch (list) {
            | [] => raise(Exceptions.Empty("FeatureBack.updateLastExn"))
            | [hd, ...rest] => [fn(hd), ...rest]
            };
          list |> Caml.List.rev |> Config.fromList;
        }
      )
    };

  let updateLast = (fn, ds) =>
    try (Some(updateLastExn(fn, ds))) {
    | _ => None
    };
};

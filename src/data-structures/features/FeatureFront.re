type fastGetFirst('ds, 'el) =
  | SlowGetFirst
  | GetFirstExn('ds => 'el);

type fastAddFirst('ds, 'el) =
  | SlowAddFirst
  | AddFirst(('el, 'ds) => 'ds);

type fastRemoveFirst('ds, 'el) =
  | SlowRemoveFirst
  | RemoveFirstExn('ds => 'ds);

module type Config = {
  type t('el);

  let toList: t('el) => list('el);
  let fromList: list('el) => t('el);

  let isEmpty: t('el) => bool;
  let fastGetFirst: fastGetFirst(t('el), 'el);
  let fastAddFirst: fastAddFirst(t('el), 'el);
  let fastRemoveFirst: fastRemoveFirst(t('el), 'el);
};

module Default = {
  let fastGetFirst = SlowGetFirst;
  let fastAddFirst = SlowAddFirst;
  let fastRemoveFirst = SlowRemoveFirst;
};

module type Interface = {
  type tFront('el);

  /**
`getFirst(ds)` returns an option containing the first element of the data
structure `ds` if it exists, `None` otherwise.

```
getFirst([1, 2, 3, 4])  // Some(1)
getFirst([])            // None
```
   */
  let getFirst: tFront('el) => option('el);

  /**
`getFirstExn(ds)` returns the first element of the data structure `ds` if it
exists, raises an exception otherwise.

```
getFirstExn([1, 2, 3, 4])  // 1
getFirstExn([])            // raises exception
```
   */
  let getFirstExn: tFront('el) => 'el;

  /**
`getFirstN(n, ds)` returns an option containing the first `n` elements of the
data structure `ds` if they exist, `None` otherwise.

```
getFirstN(2, [1, 2, 3, 4])  // Some([1, 2])
getFirstN(1, [1, 2, 3, 4])  // Some([1])
getFirstN(0, [])            // Some([])
getFirstN(1000, [1, 2])     // None
getFirstN(1, [])            // None
```
   */
  let getFirstN: (int, tFront('el)) => option(tFront('el));

  /**
`getFirstNExn(n, ds)` returns the first `n` elements of the data structure `ds`
if they exist, raises an exception otherwise.

```
getFirstNExn(2, [1, 2, 3, 4])  // [1, 2]
getFirstNExn(1, [1, 2, 3, 4])  // [1]
getFirstNExn(0, [])            // []
getFirstNExn(1000, [1, 2])     // raises exception
getFirstNExn(1, [])            // raises exception
```
   */
  let getFirstNExn: (int, tFront('el)) => tFront('el);

  /**
`addFirst(el, ds)` returns a new data structure with `el` added as the first
element of the given data structure `ds`.

```
addFirst(9, [1, 2, 3])  // [9, 1, 2, 3]
addFirst(9, [])         // [9]
```
   */
  let addFirst: ('el, tFront('el)) => tFront('el);

  /**
`removeFirst(ds)` returns an option containing a new data structure with the
first element of the given data structure `ds` removed if it exists, None
otherwise.

__Note: Use `getFirst` to access the first element if needed.__

```
removeFirst([1, 2, 3])  // Some([2, 3])
removeFirst([])         // None
```
   */
  let removeFirst: tFront('el) => option(tFront('el));

  /**
`removeFirstExn(ds)` returns a new data structure with the first element of the
given data structure `ds` removed if it exists, raises an exception otherwise.

__Note: Use `getFirst` to access the first element if needed.__

```
removeFirstExn([1, 2, 3])  // [2, 3]
removeFirstExn([])         // raises exception
```
   */
  let removeFirstExn: tFront('el) => tFront('el);

  /**
`removeFirstN(n, ds)` returns an option containing a new data structure with the
first `n` elements of the given data structure `ds` removed if they exist, None
otherwise.

__Note: Use `getFirstN` to access the first elements if needed.__

```
removeFirstN(1, [1, 2, 3])     // Some([2, 3])
removeFirstN(2, [1, 2, 3])     // Some([3])
removeFirstN(0, [])            // Some([])
removeFirstN(1000, [1, 2, 3])  // None
removeFirstN(1, [])            // None

```
   */
  let removeFirstN: (int, tFront('el)) => option(tFront('el));

  /**
`removeFirstNExn(n, ds)` returns a new data structure with the first `n`
elements of the given data structure `ds` removed if they exist, raises an
exception otherwise.

__Note: Use `getFirstN` to access the first elements if needed.__

```
removeFirstNExn(1, [1, 2, 3])     // [2, 3]
removeFirstNExn(2, [1, 2, 3])     // [3]
removeFirstNExn(0, [])            // []
removeFirstNExn(1000, [1, 2, 3])  // raises exception
removeFirstNExn(1, [])            // raises exception

```
   */
  let removeFirstNExn: (int, tFront('el)) => tFront('el);

  /**
`updateFirst(fn, ds)` returns an option containing a new data structure with the
first element of the given data structure `ds` updated by `fn` if it exists,
None otherwise.

```
updateFirst(x => x + 1, [1, 2, 3])  // Some([2, 2, 3])
updateFirst(x => x + 1, [])         // None
```
   */
  let updateFirst: ('el => 'el, tFront('el)) => option(tFront('el));

  /**
`updateFirstExn(fn, ds)` returns a new data structure with the first element of
the given data structure `ds` updated by `fn` if it exists, raises an exception
otherwise.

```
updateFirstExn(x => x + 1, [1, 2, 3])  // [2, 2, 3]
updateFirstExn(x => x + 1, [])         // raises exception
```
   */
  let updateFirstExn: ('el => 'el, tFront('el)) => tFront('el);

  let match1Exn: tFront('el) => ('el, tFront('el));
  let match2Exn: tFront('el) => ('el, 'el, tFront('el));
  let match3Exn: tFront('el) => ('el, 'el, 'el, tFront('el));
  let match4Exn: tFront('el) => ('el, 'el, 'el, 'el, tFront('el));
  let match5Exn: tFront('el) => ('el, 'el, 'el, 'el, 'el, tFront('el));
  let match6Exn: tFront('el) => ('el, 'el, 'el, 'el, 'el, 'el, tFront('el));
  let match7Exn:
    tFront('el) => ('el, 'el, 'el, 'el, 'el, 'el, 'el, tFront('el));

  let match1: tFront('el) => option(('el, tFront('el)));
  let match2: tFront('el) => option(('el, 'el, tFront('el)));
  let match3: tFront('el) => option(('el, 'el, 'el, tFront('el)));
  let match4: tFront('el) => option(('el, 'el, 'el, 'el, tFront('el)));
  let match5:
    tFront('el) => option(('el, 'el, 'el, 'el, 'el, tFront('el)));
  let match6:
    tFront('el) => option(('el, 'el, 'el, 'el, 'el, 'el, tFront('el)));
  let match7:
    tFront('el) => option(('el, 'el, 'el, 'el, 'el, 'el, 'el, tFront('el)));
};

module Add =
       (Config: Config)
       : (Interface with type tFront('el) = Config.t('el)) => {
  type tFront('el) = Config.t('el);

  let getFirstExn =
    switch (Config.fastGetFirst) {
    | GetFirstExn(getFirstExn) => getFirstExn
    | _ => (
        ds => {
          let list = Config.toList(ds);
          CamlListCore.getFirstExn(list);
        }
      )
    };

  let getFirst = ds =>
    try (Some(getFirstExn(ds))) {
    | _ => None
    };

  let getFirstNExn =
    switch (Config.fastGetFirst, Config.fastRemoveFirst) {
    | (GetFirstExn(getFirstExn), RemoveFirstExn(removeFirstExn)) => (
        (count, ds) => {
          let ds = ref(ds);
          let result = ref([]);
          for (_i in 0 to count - 1) {
            result := [getFirstExn(ds^), ...result^];
            ds := removeFirstExn(ds^);
          };
          result^ |> Caml.List.rev |> Config.fromList;
        }
      )
    | _ => (
        (count, ds) => {
          let list = Config.toList(ds);
          let list = ref(list);
          let result = ref([]);
          for (_i in 0 to count - 1) {
            result := [CamlListCore.getFirstExn(list^), ...result^];
            list := CamlListCore.removeFirstExn(list^);
          };
          result^ |> Caml.List.rev |> Config.fromList;
        }
      )
    };

  let getFirstN = (count, ds) =>
    try (Some(getFirstNExn(count, ds))) {
    | _ => None
    };

  let addFirst =
    switch (Config.fastAddFirst) {
    | AddFirst(addFirst) => addFirst
    | _ => (
        (el, ds) => {
          let list = Config.toList(ds);
          let list = [el, ...list];
          Config.fromList(list);
        }
      )
    };

  let removeFirstExn =
    switch (Config.fastRemoveFirst) {
    | RemoveFirstExn(removeFirstExn) => removeFirstExn
    | _ => (
        ds => {
          let list = Config.toList(ds);
          switch (list) {
          | [] => raise(Exceptions.Empty("FeatureFront.removeFirstExn"))
          | [_, ...rest] => Config.fromList(rest)
          };
        }
      )
    };

  let removeFirstNExn =
    switch (Config.fastRemoveFirst) {
    | RemoveFirstExn(removeFirstExn) => (
        (count, ds) => {
          let ds = ref(ds);
          for (_i in 0 to count - 1) {
            ds := removeFirstExn(ds^);
          };
          ds^;
        }
      )
    | _ => (
        (count, ds) => {
          let list = Config.toList(ds);
          let list = ref(list);
          for (_i in 0 to count - 1) {
            list := CamlListCore.removeFirstExn(list^);
          };
          list^ |> Config.fromList;
        }
      )
    };

  let removeFirstN = (count, ds) =>
    try (Some(removeFirstNExn(count, ds))) {
    | _ => None
    };

  let removeFirst = ds =>
    try (Some(removeFirstExn(ds))) {
    | _ => None
    };

  let updateFirstExn =
    switch (Config.fastGetFirst, Config.fastAddFirst, Config.fastRemoveFirst) {
    | (
        GetFirstExn(getFirstExn),
        AddFirst(addFirst),
        RemoveFirstExn(removeFirstExn),
      ) => (
        (fn, ds) =>
          if (Config.isEmpty(ds)) {
            raise(Exceptions.Empty("FeatureFront.updateFirstExn"));
          } else {
            let first = getFirstExn(ds);
            let rest = removeFirstExn(ds);
            let newFirst = fn(first);
            addFirst(newFirst, rest);
          }
      )
    | _ => (
        (fn, ds) => {
          let list = Config.toList(ds);
          switch (list) {
          | [] => raise(Exceptions.Empty("FeatureFront.updateFirstExn"))
          | [hd, ...rest] => Config.fromList([fn(hd), ...rest])
          };
        }
      )
    };

  let updateFirst = (fn, ds) =>
    try (Some(updateFirstExn(fn, ds))) {
    | _ => None
    };

  let match1Exn = ds => {
    let front = ds |> getFirstNExn(1) |> Config.toList;
    let rest = ds |> removeFirstNExn(1);
    switch (front) {
    | [el1] => (el1, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match2Exn = ds => {
    let front = ds |> getFirstNExn(2) |> Config.toList;
    let rest = ds |> removeFirstNExn(2);
    switch (front) {
    | [el1, el2] => (el1, el2, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match3Exn = ds => {
    let front = ds |> getFirstNExn(3) |> Config.toList;
    let rest = ds |> removeFirstNExn(3);
    switch (front) {
    | [el1, el2, el3] => (el1, el2, el3, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match4Exn = ds => {
    let front = ds |> getFirstNExn(4) |> Config.toList;
    let rest = ds |> removeFirstNExn(4);
    switch (front) {
    | [el1, el2, el3, el4] => (el1, el2, el3, el4, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match5Exn = ds => {
    let front = ds |> getFirstNExn(5) |> Config.toList;
    let rest = ds |> removeFirstNExn(5);
    switch (front) {
    | [el1, el2, el3, el4, el5] => (el1, el2, el3, el4, el5, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match6Exn = ds => {
    let front = ds |> getFirstNExn(6) |> Config.toList;
    let rest = ds |> removeFirstNExn(6);
    switch (front) {
    | [el1, el2, el3, el4, el5, el6] => (el1, el2, el3, el4, el5, el6, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match7Exn = ds => {
    let front = ds |> getFirstNExn(7) |> Config.toList;
    let rest = ds |> removeFirstNExn(7);
    switch (front) {
    | [el1, el2, el3, el4, el5, el6, el7] => (
        el1,
        el2,
        el3,
        el4,
        el5,
        el6,
        el7,
        rest,
      )
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match1 = ds =>
    try (Some(match1Exn(ds))) {
    | _ => None
    };

  let match2 = ds =>
    try (Some(match2Exn(ds))) {
    | _ => None
    };

  let match3 = ds =>
    try (Some(match3Exn(ds))) {
    | _ => None
    };

  let match4 = ds =>
    try (Some(match4Exn(ds))) {
    | _ => None
    };

  let match5 = ds =>
    try (Some(match5Exn(ds))) {
    | _ => None
    };

  let match6 = ds =>
    try (Some(match6Exn(ds))) {
    | _ => None
    };

  let match7 = ds =>
    try (Some(match7Exn(ds))) {
    | _ => None
    };
};

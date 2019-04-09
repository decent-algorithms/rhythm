type fastAddFirst('ds, 'el) =
  | SlowAddFirst
  | AddFirst(('el, 'ds) => 'ds);

type fastRemoveFirst('ds, 'el) =
  | SlowRemoveFirst
  | RemoveFirstExn('ds => 'ds);

module type Config = {
  include FeatureFrontCommon.Config;
  let fastAddFirst: fastAddFirst(t('el), 'el);
  let fastRemoveFirst: fastRemoveFirst(t('el), 'el);
};

module Default = {
  include FeatureFrontCommon.Default;
  let fastAddFirst = SlowAddFirst;
  let fastRemoveFirst = SlowRemoveFirst;
};

module type Interface = {
  type tFrontImmutable('el);
  include
    FeatureFrontCommon.Interface with
      type tFrontCommon('el) = tFrontImmutable('el);

  /**
`addFirst(el, ds)` returns a new data structure with `el` added as the first
element of the given data structure `ds`.

```
addFirst(9, [1, 2, 3])  // [9, 1, 2, 3]
addFirst(9, [])         // [9]
```
   */
  let addFirst: ('el, tFrontImmutable('el)) => tFrontImmutable('el);

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
  let removeFirst: tFrontImmutable('el) => option(tFrontImmutable('el));

  /**
`removeFirstExn(ds)` returns a new data structure with the first element of the
given data structure `ds` removed if it exists, raises an exception otherwise.

__Note: Use `getFirst` to access the first element if needed.__

```
removeFirstExn([1, 2, 3])  // [2, 3]
removeFirstExn([])         // raises exception
```
   */
  let removeFirstExn: tFrontImmutable('el) => tFrontImmutable('el);

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
  let removeFirstN:
    (int, tFrontImmutable('el)) => option(tFrontImmutable('el));

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
  let removeFirstNExn: (int, tFrontImmutable('el)) => tFrontImmutable('el);

  /**
`updateFirst(fn, ds)` returns an option containing a new data structure with the
first element of the given data structure `ds` updated by `fn` if it exists,
None otherwise.

```
updateFirst(x => x + 1, [1, 2, 3])  // Some([2, 2, 3])
updateFirst(x => x + 1, [])         // None
```
   */
  let updateFirst:
    ('el => 'el, tFrontImmutable('el)) => option(tFrontImmutable('el));

  /**
`updateFirstExn(fn, ds)` returns a new data structure with the first element of
the given data structure `ds` updated by `fn` if it exists, raises an exception
otherwise.

```
updateFirstExn(x => x + 1, [1, 2, 3])  // [2, 2, 3]
updateFirstExn(x => x + 1, [])         // raises exception
```
   */
  let updateFirstExn:
    ('el => 'el, tFrontImmutable('el)) => tFrontImmutable('el);
};

module Add =
       (Config: Config)
       : (Interface with type tFrontImmutable('el) = Config.t('el)) => {
  include FeatureFrontCommon.Add(Config);

  type tFrontImmutable('el) = Config.t('el);

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
            list := CamlListCore.dropFirstExn(list^);
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
};

type fastGetFirst('ds, 'el) =
  | SlowGetFirst
  | GetFirstExn('ds => 'el);

type fastDropFirst('ds, 'el) =
  | SlowDropFirst
  | DropFirstExn('ds => 'ds);

module type Config = {
  type t('el);

  let toList: t('el) => list('el);
  let fromList: list('el) => t('el);

  let isEmpty: t('el) => bool;
  let fastGetFirst: fastGetFirst(t('el), 'el);
  let fastDropFirst: fastDropFirst(t('el), t('el));
};

module Default = {
  let fastGetFirst = SlowGetFirst;
  let fastDropFirst = SlowDropFirst;
};

module type Interface = {
  type tFrontCommon('el);

  /**
`getFirst(ds)` returns an option containing the first element of the data
structure `ds` if it exists, `None` otherwise.

```
getFirst([1, 2, 3, 4])  // Some(1)
getFirst([])            // None
```
   */
  let getFirst: tFrontCommon('el) => option('el);

  /**
`getFirstExn(ds)` returns the first element of the data structure `ds` if it
exists, raises an exception otherwise.

```
getFirstExn([1, 2, 3, 4])  // 1
getFirstExn([])            // raises exception
```
   */
  let getFirstExn: tFrontCommon('el) => 'el;

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
  let getFirstN: (int, tFrontCommon('el)) => option(tFrontCommon('el));

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
  let getFirstNExn: (int, tFrontCommon('el)) => tFrontCommon('el);

  /**
`dropFirst(ds)` returns an option containing a new data structure with the
first element of the given data structure `ds` removed if it exists, None
otherwise.

__Note: This does NOT mutate the given data structure.__
__Note: Use `getFirst` to access the first element if needed.__

```
dropFirst([1, 2, 3])  // Some([2, 3])
dropFirst([])         // None
```
   */
  let dropFirst: tFrontCommon('el) => option(tFrontCommon('el));

  /**
`dropFirstExn(ds)` returns a new data structure with the first element of the
given data structure `ds` removed if it exists, raises an exception otherwise.

__Note: This does NOT mutate the given data structure.__
__Note: Use `getFirst` to access the first element if needed.__

```
dropFirstExn([1, 2, 3])  // [2, 3]
dropFirstExn([])         // raises exception
```
   */
  let dropFirstExn: tFrontCommon('el) => tFrontCommon('el);

  /**
`dropFirstN(n, ds)` returns an option containing a new data structure with the
first `n` elements of the given data structure `ds` removed if they exist, None
otherwise.

__Note: This does NOT mutate the given data structure.__
__Note: Use `getFirstN` to access the first elements if needed.__

```
dropFirstN(1, [1, 2, 3])     // Some([2, 3])
dropFirstN(2, [1, 2, 3])     // Some([3])
dropFirstN(0, [])            // Some([])
dropFirstN(1000, [1, 2, 3])  // None
dropFirstN(1, [])            // None

```
   */
  let dropFirstN: (int, tFrontCommon('el)) => option(tFrontCommon('el));

  /**
`dropFirstNExn(n, ds)` returns a new data structure with the first `n`
elements of the given data structure `ds` removed if they exist, raises an
exception otherwise.

__Note: This does NOT mutate the given data structure.__
__Note: Use `getFirstN` to access the first elements if needed.__

```
dropFirstNExn(1, [1, 2, 3])     // [2, 3]
dropFirstNExn(2, [1, 2, 3])     // [3]
dropFirstNExn(0, [])            // []
dropFirstNExn(1000, [1, 2, 3])  // raises exception
dropFirstNExn(1, [])            // raises exception

```
   */
  let dropFirstNExn: (int, tFrontCommon('el)) => tFrontCommon('el);

  let match1Exn: tFrontCommon('el) => ('el, tFrontCommon('el));
  let match2Exn: tFrontCommon('el) => ('el, 'el, tFrontCommon('el));
  let match3Exn: tFrontCommon('el) => ('el, 'el, 'el, tFrontCommon('el));
  let match4Exn:
    tFrontCommon('el) => ('el, 'el, 'el, 'el, tFrontCommon('el));
  let match5Exn:
    tFrontCommon('el) => ('el, 'el, 'el, 'el, 'el, tFrontCommon('el));
  let match6Exn:
    tFrontCommon('el) => ('el, 'el, 'el, 'el, 'el, 'el, tFrontCommon('el));
  let match7Exn:
    tFrontCommon('el) =>
    ('el, 'el, 'el, 'el, 'el, 'el, 'el, tFrontCommon('el));

  let match1: tFrontCommon('el) => option(('el, tFrontCommon('el)));
  let match2: tFrontCommon('el) => option(('el, 'el, tFrontCommon('el)));
  let match3:
    tFrontCommon('el) => option(('el, 'el, 'el, tFrontCommon('el)));
  let match4:
    tFrontCommon('el) => option(('el, 'el, 'el, 'el, tFrontCommon('el)));
  let match5:
    tFrontCommon('el) =>
    option(('el, 'el, 'el, 'el, 'el, tFrontCommon('el)));
  let match6:
    tFrontCommon('el) =>
    option(('el, 'el, 'el, 'el, 'el, 'el, tFrontCommon('el)));
  let match7:
    tFrontCommon('el) =>
    option(('el, 'el, 'el, 'el, 'el, 'el, 'el, tFrontCommon('el)));
};

module Add =
       (Config: Config)
       : (Interface with type tFrontCommon('el) = Config.t('el)) => {
  type tFrontCommon('el) = Config.t('el);

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
    switch (Config.fastGetFirst, Config.fastDropFirst) {
    | (GetFirstExn(getFirstExn), DropFirstExn(dropFirstExn)) => (
        (count, ds) => {
          let ds = ref(ds);
          let result = ref([]);
          for (_i in 0 to count - 1) {
            result := [getFirstExn(ds^), ...result^];
            ds := dropFirstExn(ds^);
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
            list := CamlListCore.dropFirstExn(list^);
          };
          result^ |> Caml.List.rev |> Config.fromList;
        }
      )
    };

  let getFirstN = (count, ds) =>
    try (Some(getFirstNExn(count, ds))) {
    | _ => None
    };

  let dropFirstExn =
    switch (Config.fastDropFirst) {
    | DropFirstExn(dropFirstExn) => dropFirstExn
    | _ => (
        ds => {
          let list = Config.toList(ds);
          switch (list) {
          | [] => raise(Exceptions.Empty("FeatureFront.dropFirstExn"))
          | [_, ...rest] => Config.fromList(rest)
          };
        }
      )
    };

  let dropFirstNExn =
    switch (Config.fastDropFirst) {
    | DropFirstExn(dropFirstExn) => (
        (count, ds) => {
          let ds = ref(ds);
          for (_i in 0 to count - 1) {
            ds := dropFirstExn(ds^);
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

  let dropFirstN = (count, ds) =>
    try (Some(dropFirstNExn(count, ds))) {
    | _ => None
    };

  let dropFirst = ds =>
    try (Some(dropFirstExn(ds))) {
    | _ => None
    };

  let match1Exn = ds => {
    let front = ds |> getFirstNExn(1) |> Config.toList;
    let rest = ds |> dropFirstNExn(1);
    switch (front) {
    | [el1] => (el1, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match2Exn = ds => {
    let front = ds |> getFirstNExn(2) |> Config.toList;
    let rest = ds |> dropFirstNExn(2);
    switch (front) {
    | [el1, el2] => (el1, el2, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match3Exn = ds => {
    let front = ds |> getFirstNExn(3) |> Config.toList;
    let rest = ds |> dropFirstNExn(3);
    switch (front) {
    | [el1, el2, el3] => (el1, el2, el3, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match4Exn = ds => {
    let front = ds |> getFirstNExn(4) |> Config.toList;
    let rest = ds |> dropFirstNExn(4);
    switch (front) {
    | [el1, el2, el3, el4] => (el1, el2, el3, el4, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match5Exn = ds => {
    let front = ds |> getFirstNExn(5) |> Config.toList;
    let rest = ds |> dropFirstNExn(5);
    switch (front) {
    | [el1, el2, el3, el4, el5] => (el1, el2, el3, el4, el5, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match6Exn = ds => {
    let front = ds |> getFirstNExn(6) |> Config.toList;
    let rest = ds |> dropFirstNExn(6);
    switch (front) {
    | [el1, el2, el3, el4, el5, el6] => (el1, el2, el3, el4, el5, el6, rest)
    | _ => raise(Exceptions.InternalError("FeatureFront.matchNExn"))
    };
  };

  let match7Exn = ds => {
    let front = ds |> getFirstNExn(7) |> Config.toList;
    let rest = ds |> dropFirstNExn(7);
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

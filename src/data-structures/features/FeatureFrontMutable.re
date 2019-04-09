module type Config = {
  include FeatureFrontCommon.Config;

  /*
   * These must be provided, there is no default way to mutate the underlying
   * structure without these functions provided.
   */
  let addFirst: ('el, t('el)) => unit;
  let removeFirstExn: (t('el)) => unit;
};

module Default = {
  include FeatureFrontCommon.Default;
};

module type Interface = {
  type tFrontMutable('el);
  include
    FeatureFrontCommon.Interface with
      type tFrontCommon('el) = tFrontMutable('el);

  /**
`addFirst(el, ds)` mutates `ds` so that `el` is added as the first element.

```
addFirst(9, [1, 2, 3])  // (), mutates ds to: [9, 1, 2, 3]
addFirst(9, [])         // (), mutates ds to: [9]
```
   */
  let addFirst: ('el, tFrontMutable('el)) => unit;

  /**
`removeFirst(ds)` mutates `ds` so that the first element is removed if it
exists. Ok() is returned if successful, Error(exn) otherwise.

__Note: Use `dropFirst` to perform the same operation without mutations.__
__Note: Use `getFirst` to access the first element if needed.__

```
removeFirst([1, 2, 3])  // Ok(), mutates ds to: [2, 3]
removeFirst([])         // Error(...), does not mutate ds
```
   */
  let removeFirst: tFrontMutable('el) => result(unit, exn);

  /**
`removeFirstExn(ds)` mutates `ds` so that the first element is removed if it
exists. Nothing (a unit) is returned if successful, raises an exception
otherwise.

__Note: Use `dropFirstExn` to perform the same operation without mutations.__
__Note: Use `getFirstExn` to access the first element if needed.__

```
removeFirstExn([1, 2, 3])  // (), mutates ds to: [2, 3]
removeFirstExn([])         // raises exception
   */
  let removeFirstExn: tFrontMutable('el) => unit;

  /**
`removeFirstN(n, ds)` mutates `ds` so that the first `n` elements are removed.
Ok() is returned if successful, Error(exn) otherwise.

__Note: Use `dropFirstN` to perform the same operation without mutations.__
__Note: Use `getFirstN` to access the first elements if needed.__

```
removeFirstN(1, [1, 2, 3])     // Ok(), mutates ds to: [2, 3]
removeFirstN(2, [1, 2, 3])     // Ok(), mutates ds to: [3]
removeFirstN(0, [])            // Ok(), no mutations necessary
removeFirstN(1000, [1, 2, 3])  // Error(...), does not mutate ds
removeFirstN(1, [])            // Error(...), does not mutate ds

```
   */
  let removeFirstN: (int, tFrontMutable('el)) => result(unit, exn);

  /**
`removeFirstNExn(n, ds)` mutates `ds` so that the first `n` elements are
removed. Nothing (a unit) is returned if successful, raises an exception
otherwise.

__Note: Use `dropFirstNExn` to perform the same operation without mutations.__
__Note: Use `getFirstNExn` to access the first elements if needed.__

```
removeFirstNExn(1, [1, 2, 3])     // (), mutates ds to: [2, 3]
removeFirstNExn(2, [1, 2, 3])     // (), mutates ds to: [3]
removeFirstNExn(0, [])            // (), no mutations necessary
removeFirstNExn(1000, [1, 2, 3])  // raises exception
removeFirstNExn(1, [])            // raises exception
```
   */
  let removeFirstNExn: (int, tFrontMutable('el)) => unit;

  /**
`updateFirst(fn, ds)` mutates `ds` so that the first elemented is updated by
`fn` if it exists. Ok() is returned if successful, Error(exn) otherwise.

```
updateFirst(x => x + 1, [1, 2, 3])  // Ok(), mutates ds to: [2, 2, 3]
updateFirst(x => x + 1, [])         // Error(...), does not mutate ds
```
   */
  let updateFirst: ('el => 'el, tFrontMutable('el)) => result(unit, exn);

  /**
`updateFirst(fn, ds)` mutates `ds` so that the first elemented is updated by
`fn` if it exists. Nothing (a unit) is returned if successful, raises an
exception otherwise.

```
updateFirst(x => x + 1, [1, 2, 3])  // (), mutates ds to: [2, 2, 3]
updateFirst(x => x + 1, [])         // raises exception
```
   */
  let updateFirstExn: ('el => 'el, tFrontMutable('el)) => unit;
};

module Add =
       (Config: Config)
       : (Interface with type tFrontMutable('el) = Config.t('el)) => {
  include FeatureFrontCommon.Add(Config);

  type tFrontMutable('el) = Config.t('el);

  let addFirst = Config.addFirst;

  let removeFirstExn = Config.removeFirstExn;

  let removeFirstNExn = (count, ds) => {
    for (_i in 0 to count - 1) {
      removeFirstExn(ds);
    };
  };

  let removeFirstN = (count, ds) =>
    try (Ok(removeFirstNExn(count, ds))) {
    | e => Error(e)
    };

  let removeFirst = ds =>
    try (Ok(removeFirstExn(ds))) {
    | e => Error(e)
    };

  let updateFirstExn =
    (fn, ds) =>
      if (Config.isEmpty(ds)) {
        raise(Exceptions.Empty("FeatureFront.updateFirstExn"));
      } else {
        let first = getFirstExn(ds);
        removeFirstExn(ds);
        let newFirst = fn(first);
        addFirst(newFirst, ds);
      };

  let updateFirst = (fn, ds) =>
    try (Ok(updateFirstExn(fn, ds))) {
    | e => Error(e)
    };
};

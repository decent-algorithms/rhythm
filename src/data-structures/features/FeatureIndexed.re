module type Config = {
  type t('el);
  let getIndexExn: (int, t('el)) => 'el;
};

module type Interface = {
  type tIndexed('el);

  /**
`getIndex(i, ds)` returns an option containing the element of the data
structure `ds` at index `i` if it exists, `None` otherwise.

```
getIndex(0, [0, 1, 2, 3, 4])   // Some(0)
getIndex(2, [0, 1, 2, 3, 4])   // Some(2)
getIndex(-1, [0, 1, 2, 3, 4])  // None
getIndex(10, [0, 1, 2, 3, 4])  // None
getIndex(0, [])                // None
```
   */
  let getIndex: (int, tIndexed('el)) => option('el);

  /**
`getIndexExn(i, ds)` returns the element of the data structure `ds` at index
`i` if it exists, raises an exception othewise.

```
getIndexExn(0, [0, 1, 2, 3, 4])   // 0
getIndexExn(2, [0, 1, 2, 3, 4])   // 2
getIndexExn(-1, [0, 1, 2, 3, 4])  // raises exception
getIndexExn(10, [0, 1, 2, 3, 4])  // raises exception
getIndexExn(0, [])                // raises exception
```
   */
  let getIndexExn: (int, tIndexed('el)) => 'el;
};

module Add =
       (Config: Config)
       : (Interface with type tIndexed('el) = Config.t('el)) => {
  type tIndexed('el) = Config.t('el);

  let getIndexExn = Config.getIndexExn;
  let getIndex = (index, ds) =>
    try (Some(getIndexExn(index, ds))) {
    | _ => None
    };
};

module type Config = {
  type t('el);

  let length: t('el) => int;
  let getIndexExn: (int, t('el)) => 'el;
  let setIndexExn: (int, 'el, t('el)) => unit;
};

module type Interface = {
  type tMutableIndexed('el);

  /**
`setIndex(i, el, ds)` changes index `i` of `ds` to be `el`. The function
returns a `result` that is either Ok if the call was successful, or an
Error containing an exception if the call was not successful (e.g. there
was an index out of bounds exception).

```
setIndex(0, 100, [| 0, 1, 2 |]) // Ok(), mutated structure: [| 100, 1, 2 |]
setIndex(2, 100, [| 0, 1, 2 |]) // Ok(), mutated structure: [| 0, 1, 100 |]
setIndex(3, 100, [| 0, 1, 2 |]) // Error(...), structure doesn't change
setIndex(-1, 100, [| 0 ])       // Error(...), structure doesn't change
```
   */
  let setIndex: (int, 'el, tMutableIndexed('el)) => result(unit, exn);

  /**
`setIndexExn(i, el, ds)` changes index `i` of `ds` to be `el`. The function
returns nothing (a unit) if the call was successful, or raises an
exception if the call was not successful (e.g. there
was an index out of bounds exception).

```
setIndexExn(0, 100, [| 0, 1, 2 |]) // (), mutated structure: [| 100, 1, 2 |]
setIndexExn(2, 100, [| 0, 1, 2 |]) // (), mutated structure: [| 0, 1, 100 |]
setIndexExn(3, 100, [| 0, 1, 2 |]) // raises exception, structure doesn't change
setIndexExn(-1, 100, [| 0 ])       // raises exception, structure doesn't change
```
   */
  let setIndexExn: (int, 'el, tMutableIndexed('el)) => unit;

  /**
`updateIndex(i, fn, ds)` changes the `value` at index `i` of `ds` to be
`fn(value)`. The function returns a `result` that is either Ok if the call was
successful, or an Error containing an exception if the call was not successful
(e.g. there was an index out of bounds exception).

```
let add100 = x => x + 100;
updateIndex(0, add100, [| 0, 1, 2 |]) // Ok(), mutated structure: [| 100, 1, 2 |]
updateIndex(2, add100, [| 0, 1, 2 |]) // Ok(), mutated structure: [| 0, 1, 102 |]
updateIndex(3, add100, [| 0, 1, 2 |]) // Error(...), structure doesn't change
updateIndex(-1, add100, [| 0 ])       // Error(...), structure doesn't change
```
   */
  let updateIndex:
    (int, 'el => 'el, tMutableIndexed('el)) => result(unit, exn);

  /**
`updateIndexExn(i, fn, ds)` changes the `value` at index `i` of `ds` to be
`fn(value)`. The function returns nothing (a unit) if the call was
successful, or raises an exception if the call was not successful
(e.g. there was an index out of bounds exception).

```
let add100 = x => x + 100;
updateIndexExn(0, add100, [| 0, 1, 2 |]) // (), mutated structure: [| 100, 1, 2 |]
updateIndexExn(2, add100, [| 0, 1, 2 |]) // (), mutated structure: [| 0, 1, 102 |]
updateIndexExn(3, add100, [| 0, 1, 2 |]) // raises exception, structure doesn't change
updateIndexExn(-1, add100, [| 0 ])       // raises exception, structure doesn't change
```
   */
  let updateIndexExn: (int, 'el => 'el, tMutableIndexed('el)) => unit;

  /**
`swap(i, j, ds)` swaps the values at indices `i` and `j` within `ds`. The
function returns a `result` that is either Ok if the call was successful, or an
Error containing an exceptions if the call was not successful (e.g. there
was an index out of bounds exception).

```
swap(0, 2, [| 0, 1, 2 |])   // Ok(), mutated structure: [| 2, 1, 0 |]
swap(1, 2, [| 0, 1, 2 |])   // Ok(), mutated structure: [| 0, 2, 1 |]
swap(2, 1, [| 0, 1, 2 |])   // Ok(), mutated structure: [| 0, 2, 1 |]
swap(0, 100, [| 0, 1, 2 |]) // Error(...), structure doesn't change
swap(-1, 1, [| 0, 1, 2 |])  // Error(...), structure doesn't change
```
   */
  let swap: (int, int, tMutableIndexed('el)) => result(unit, exn);

  /**
`swapExn(i, j, ds)` swaps the values at indices `i` and `j` within `ds`. The
function returns nothin (a unit) if the call was successful, or
raises an exceptions if the call was not successful (e.g. there
was an index out of bounds exception).

```
swapExn(0, 2, [| 0, 1, 2 |])   // (), mutated structure: [| 2, 1, 0 |]
swapExn(1, 2, [| 0, 1, 2 |])   // (), mutated structure: [| 0, 2, 1 |]
swapExn(2, 1, [| 0, 1, 2 |])   // (), mutated structure: [| 0, 2, 1 |]
swapExn(0, 100, [| 0, 1, 2 |]) // raises exception, structure doesn't change
swapExn(-1, 1, [| 0, 1, 2 |])  // raises exception, structure doesn't change
```
   */
  let swapExn: (int, int, tMutableIndexed('el)) => unit;
};

module Add =
       (Config: Config)
       : (Interface with type tMutableIndexed('el) = Config.t('el)) => {
  type tMutableIndexed('el) = Config.t('el);

  let setIndexExn = Config.setIndexExn;

  let setIndex = (index, el, ds) =>
    try (
      {
        let () = setIndexExn(index, el, ds);
        Ok();
      }
    ) {
    | e => Error(e)
    };

  let updateIndexExn = (index, fn, ds) => {
    let newValue = fn(Config.getIndexExn(index, ds));
    setIndexExn(index, newValue, ds);
  };

  let updateIndex = (index, fn, ds) =>
    try (
      {
        let () = updateIndexExn(index, fn, ds);
        Ok();
      }
    ) {
    | e => Error(e)
    };

  let swapExn = (index1, index2, ds) => {
    let newIndex2 = Config.getIndexExn(index1, ds);
    let newIndex1 = Config.getIndexExn(index2, ds);
    let () = setIndexExn(index2, newIndex2, ds);
    let () = setIndexExn(index1, newIndex1, ds);
    ();
  };

  let swap = (index1, index2, ds) =>
    try (
      {
        let () = swapExn(index1, index2, ds);
        Ok();
      }
    ) {
    | e => Error(e)
    };
};

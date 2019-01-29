type dl('el) =
  | Empty
  | Leaf('el)
  | Branch(dl('el), dl('el));

type t('el) = (int, dl('el));

let make = () => (0, Empty);

let makeOne = el => (1, Leaf(el));

let length = ds => {
  let (length, _) = ds;
  length;
};

let isEmpty = ds => length(ds) === 0;

let concat = (ds1, ds2) => {
  let (length1, dl1) = ds1;
  let (length2, dl2) = ds2;
  switch (dl1, dl2) {
  | (Empty, Empty) => (0, Empty)
  | (Empty, _) => ds2
  | (_, Empty) => ds1
  | _ => (length1 + length2, Branch(dl1, dl2))
  };
};

let addFirst = (el, ds) => concat(makeOne(el), ds);

let addLast = (el, ds) => concat(ds, makeOne(el));

/*
 * TODO:
 *
 * - getFirstExn
 * - getLastExn
 * - removeFirstExn
 * - removeLastExn
 * - toList
 * - fromList
 */
let _ = ();

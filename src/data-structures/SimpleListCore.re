type t('el) = list('el);
let make = () => [];
let length = Caml.List.length;
let isEmpty = list =>
  switch (list) {
  | [] => true
  | _ => false
  };
let toList: t('el) => list('el) = list => list;
let fromList: list('el) => t('el) = list => list;

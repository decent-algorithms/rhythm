include SimpleListCore;

include FeatureSyntax.Add({
  include SimpleListCore;
  let length = Caml.List.length;
  let get = Caml.List.nth;
});

include FeatureSequence.Add(SimpleListCore);

let getFirst = list =>
  switch (list) {
  | [] => None
  | [el, ..._rest] => Some(el)
  };

let getFirstExn = list =>
  switch (list) {
  | [] => raise(Exceptions.Empty("SimpleList.getFirstExn"))
  | [el, ..._rest] => el
  };

let getIndex = (i, arr) => Syntax.(arr[i]);

let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);

let getLastExn = list => {
  let list = ref(list);
  let break = ref(false);
  while (! break^) {
    switch (list^) {
    | [] => break := true
    | [el] => break := true
    | [_, ...rest] => list := rest
    };
  };

  switch (list^) {
  | [] => raise(Exceptions.Empty("SimpleList.getLastExn"))
  | [el] => el
  /* This should not be reachable. */
  | _ => raise(Exceptions.InternalError("SimpleList.getLastExn"))
  };
};

let getLast = list =>
  try (Some(getLastExn(list))) {
  | e => None
  };

let concat = (listFirst, listLast) => listFirst @ listLast;

/* let addFirst = (el, arr) => concat([|el|], arr); */
/* let addLast = (el, arr) => concat(arr, [|el|]); */

/* let getFirstNExn = (n, arr) => {
     let len = length(arr);
     if (n < 0 || n > len) {
       raise(
         Exceptions.IndexOutOfBounds("MutableArray.getFirstNExn", n, 0, len + 1),
       );
     } else {
       init(n, i => SyntaxExn.(arr[i]));
     };
   }; */
();

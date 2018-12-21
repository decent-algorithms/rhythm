include MutableArrayCore;

include FeatureMutableSyntax.Add({
  include MutableArrayCore;
  let length = Caml.Array.length;
  let get = Caml.Array.get;
  let set = Caml.Array.set;
});

include FeatureSequence.Add(MutableArrayCore);

include FeatureFront.Add({
  include MutableArrayCore;
  open FeatureFront;
  let fastGetFirst = GetFirstExn(arr => SyntaxExn.(arr[0]));
  let fastAddFirst = SlowAddFirst;
  let fastRemoveFirst = SlowRemoveFirst;
});

include FeatureBack.Add({
  include MutableArrayCore;
  open FeatureBack;
  let fastGetLast = GetLastExn(arr => SyntaxExn.(arr[length(arr) - 1]));
  let fastAddLast = SlowAddLast;
  let fastRemoveLast = SlowRemoveLast;
});

let getIndex = (i, arr) => Syntax.(arr[i]);
let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
let setIndex = (i, value, arr) => Syntax.(arr[i] = value);
let setIndexExn = (i, value, arr) => SyntaxExn.(arr[i] = value);

let swapExn = (i, j, arr) => {
  let n = length(arr);
  if (i < 0 || i >= n) {
    raise(Exceptions.IndexOutOfBounds("MutableArray.swapExn", i, 0, n));
  } else if (j < 0 || j >= n) {
    raise(Exceptions.IndexOutOfBounds("MutableArray.swapExn", j, 0, n));
  } else {
    open SyntaxExn;
    let tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
    ();
  };
};

let swap = (i, j, arr) =>
  try (Ok(swapExn(i, j, arr))) {
  | e => Error(e)
  };

let updateIndexExn = (i, fn, arr) => {
  let n = length(arr);
  if (i < 0 || i >= n) {
    raise(
      Exceptions.IndexOutOfBounds("MutableArray.updateIndexExn", i, 0, n),
    );
  } else {
    open SyntaxExn;
    let newValue = fn(arr[i]);
    arr[i] = newValue;
    ();
  };
};

let updateIndex = (i, fn, arr) =>
  try (Ok(updateIndexExn(i, fn, arr))) {
  | e => Error(e)
  };

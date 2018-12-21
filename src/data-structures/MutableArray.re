include MutableArrayCore;

include FeatureMutableSyntax.Add({
  include MutableArrayCore;
  let get = Caml.Array.get;
  let set = Caml.Array.set;
});

include FeatureSequence.Add({
  include MutableArrayCore;
});

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

include FeatureIndexed.Add({
  include MutableArrayCore;
  let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
});

include FeatureMutableIndexed.Add({
  include MutableArrayCore;
  let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
  let setIndexExn = (i, value, arr) => SyntaxExn.(arr[i] = value);
});

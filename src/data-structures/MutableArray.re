include MutableArrayCore;

include FeatureMutableSyntax.Add({
  include MutableArrayCore;
  let get = Caml.Array.get;
  let set = Caml.Array.set;
});

include FeatureSequence.Add({
  open FeatureSequence;
  include Default;
  include MutableArrayCore;
});

include FeatureFront.Add({
  open FeatureFront;
  include Default;
  include MutableArrayCore;
  let fastGetFirst = GetFirstExn(arr => SyntaxExn.(arr[0]));
});

include FeatureBack.Add({
  open FeatureBack;
  include Default;
  include MutableArrayCore;
  let fastGetLast = GetLastExn(arr => SyntaxExn.(arr[length(arr) - 1]));
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

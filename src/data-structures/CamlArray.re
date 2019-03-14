include CamlArrayCore;

include FeatureMutableSyntax.Add({
  include CamlArrayCore;
  let get = Caml.Array.get;
  let set = Caml.Array.set;
});

include FeatureSequence.Add({
  open FeatureSequence;
  include Default;
  include CamlArrayCore;
});

include FeatureFront.Add({
  open FeatureFront;
  include Default;
  include CamlArrayCore;
  let fastGetFirst = GetFirstExn(arr => SyntaxExn.(arr[0]));
});

include FeatureBack.Add({
  open FeatureBack;
  include Default;
  include CamlArrayCore;
  let fastGetLast = GetLastExn(arr => SyntaxExn.(arr[length(arr) - 1]));
});

include FeatureIndexed.Add({
  include CamlArrayCore;
  let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
});

include FeatureMutableIndexed.Add({
  include CamlArrayCore;
  let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
  let setIndexExn = (i, value, arr) => SyntaxExn.(arr[i] = value);
});

include CamlListCore;

include FeatureSyntax.Add({
  include CamlListCore;
  let get = Caml.List.nth;
});

include FeatureSequence.Add({
  open FeatureSequence;
  include Default;
  include CamlListCore;
});

include FeatureFrontImmutable.Add({
  open FeatureFrontCommon;
  open FeatureFrontImmutable;
  include Default;
  include CamlListCore;
  let fastGetFirst = GetFirstExn(CamlListCore.getFirstExn);
  let fastDropFirst = DropFirstExn(CamlListCore.dropFirstExn);
  let fastAddFirst = AddFirst(CamlListCore.addFirst);
  let fastRemoveFirst = RemoveFirstExn(CamlListCore.dropFirstExn);
});

include FeatureBack.Add({
  open FeatureBack;
  include Default;
  include CamlListCore;
});

include FeatureIndexed.Add({
  include CamlListCore;
  let getIndexExn = (i, ds) => SyntaxExn.(ds[i]);
});

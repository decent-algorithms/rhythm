type t('el);

let make: unit => t('el);
let isEmpty: t('el) => bool;
let length: t('el) => int;

include FeatureSequence.Interface with type tSequence('el) = t('el);

include
  FeatureFrontImmutable.Interface with type tFrontImmutable('el) = t('el);

include FeatureBack.Interface with type tBack('el) = t('el);

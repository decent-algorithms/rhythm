type t('el) = array('el);

let make: unit => t('el);
let isEmpty: t('el) => bool;
let length: t('el) => int;

include
  FeatureMutableSyntax.Interface with type tMutableSyntax('el) = t('el);

include FeatureSequence.Interface with type tSequence('el) = t('el);

include FeatureFront.Interface with type tFront('el) = t('el);

include FeatureBack.Interface with type tBack('el) = t('el);

/**
 * Access functions.
 */

let getIndex: (int, t('el)) => option('el);
let getIndexExn: (int, t('el)) => 'el;

/**
 * Update functions.
 */

let setIndex: (int, 'el, t('el)) => result(unit, exn);
let setIndexExn: (int, 'el, t('el)) => unit;
let swap: (int, int, t('el)) => result(unit, exn);
let swapExn: (int, int, t('el)) => unit;
let updateIndex: (int, 'el => 'el, t('el)) => result(unit, exn);
let updateIndexExn: (int, 'el => 'el, t('el)) => unit;

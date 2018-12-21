type t('el) = list('el);

let make: unit => t('el);
let isEmpty: t('el) => bool;
let length: t('el) => int;

include FeatureSyntax.Interface with type tSyntax('el) = t('el);

include FeatureSequence.Interface with type tSequence('el) = t('el);

include FeatureFront.Interface with type tFront('el) = t('el);
/**
 * Access functions.
 */

/* let getIndex: (int, t('el)) => option('el); */
/* let getIndexExn: (int, t('el)) => 'el; */
let getLast: t('el) => option('el);
let getLastExn: t('el) => 'el;

/**
 * Add functions.
 */;

/* let addLast: ('el, t('el)) => t('el); */

/**
 * Remove functions.
 */;

/* let removeLast: t('el) => option(t('el)); */
/* let removeLastExn: t('el) => t('el); */

/**
 * Update functions.
 */;

/* let setIndex: (int, 'el, t('el)) => result(unit, exn); */
/* let setIndexExn: (int, 'el, t('el)) => unit; */
/* let swap: (int, int, t('el)) => result(unit, exn); */
/* let swapExn: (int, int, t('el)) => unit; */
/* let updateIndex: (int, 'el => 'el, t('el)) => result(unit, exn); */
/* let updateIndexExn: (int, 'el => 'el, t('el)) => unit; */

/**
 * Match functions.
 */;

/* let match1: t('el) => option(('el, t('el)));
   let match2: t('el) => option(('el, 'el, t('el)));
   let match3: t('el) => option(('el, 'el, 'el, t('el)));
   let match4: t('el) => option(('el, 'el, 'el, 'el, t('el)));
   let match5: t('el) => option(('el, 'el, 'el, 'el, 'el, t('el)));
   let match6: t('el) => option(('el, 'el, 'el, 'el, 'el, 'el, t('el)));
   let match7: t('el) => option(('el, 'el, 'el, 'el, 'el, 'el, 'el, t('el)));

   let match1Exn: t('el) => ('el, t('el));
   let match2Exn: t('el) => ('el, 'el, t('el));
   let match3Exn: t('el) => ('el, 'el, 'el, t('el));
   let match4Exn: t('el) => ('el, 'el, 'el, 'el, t('el));
   let match5Exn: t('el) => ('el, 'el, 'el, 'el, 'el, t('el));
   let match6Exn: t('el) => ('el, 'el, 'el, 'el, 'el, 'el, t('el));
   let match7Exn: t('el) => ('el, 'el, 'el, 'el, 'el, 'el, 'el, t('el)); */

type t('el) = array('el);

module Syntax: {
  module Array: {
    let get: (t('el), int) => option('el);
    let set: (t('el), int, 'el) => result(unit, exn);
  };
};

module SyntaxNested: {
  module Array: {
    let get: (option(t('el)), int) => option('el);
    let set: (option(t('el)), int, 'el) => result(unit, exn);
  };
};

module SyntaxExn: {
  module Array: {
    let get: (t('el), int) => 'el;
    let set: (t('el), int, 'el) => unit;
  };
};

module SyntaxReset: {module Array: {};};

/**
 * Creation functions.
 */

let make: unit => t('el);
let init: (int, int => 'el) => t('el);

/**
 * Information functions.
 */

let isEmpty: t('el) => bool;
let length: t('el) => int;

/**
 * Access functions.
 */

let getFirst: t('el) => option('el);
let getFirstExn: t('el) => 'el;
let getIndex: (int, t('el)) => option('el);
let getIndexExn: (int, t('el)) => 'el;
let getLast: t('el) => option('el);
let getLastExn: t('el) => 'el;

/**
 * Add functions.
 */

let addFirst: ('el, t('el)) => t('el);
let addLast: ('el, t('el)) => t('el);

/**
 * Remove functions.
 */

let removeFirst: t('el) => option(t('el));
let removeFirstExn: t('el) => t('el);
let removeLast: t('el) => option(t('el));
let removeLastExn: t('el) => t('el);

/**
 * Update functions.
 */

let setIndex: (int, 'el, t('el)) => result(unit, exn);
let setIndexExn: (int, 'el, t('el)) => unit;
let swap: (int, int, t('el)) => result(unit, exn);
let swapExn: (int, int, t('el)) => unit;
let updateIndex: (int, 'el => 'el, t('el)) => result(unit, exn);
let updateIndexExn: (int, 'el => 'el, t('el)) => unit;

/**
 * Iteration functions.
 */

let every: ('el => bool, t('el)) => bool;
let everyi: ((int, 'el) => bool, t('el)) => bool;
let forEach: ('el => unit, t('el)) => unit;
let forEachi: ((int, 'el) => unit, t('el)) => unit;
let none: ('el => bool, t('el)) => bool;
let nonei: ((int, 'el) => bool, t('el)) => bool;
let some: ('el => bool, t('el)) => bool;
let somei: ((int, 'el) => bool, t('el)) => bool;

/**
 * Sequence functions.
 */

let filterDrop: ('el => bool, t('el)) => t('el);
let filterDropi: ((int, 'el) => bool, t('el)) => t('el);
let filterKeep: ('el => bool, t('el)) => t('el);
let filterKeepi: ((int, 'el) => bool, t('el)) => t('el);
let map: ('a => 'b, t('a)) => t('b);
let mapi: ((int, 'a) => 'b, t('a)) => t('b);
let reverse: t('el) => t('el);
let reduce: (('acc, 'el) => 'acc, 'acc, t('el)) => 'acc;
let reducei: (('acc, int, 'el) => 'acc, 'acc, t('el)) => 'acc;
let reduceReverse: (('acc, 'el) => 'acc, 'acc, t('el)) => 'acc;
let reduceReversei: (('acc, int, 'el) => 'acc, 'acc, t('el)) => 'acc;

/**
 * Multi-sequence functions.
 */

let flatten: t(t('el)) => t('el);
let concat: (t('el), t('el)) => t('el);

/**
 * Match functions.
 */

let match1: t('el) => option(('el, t('el)));
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
let match7Exn: t('el) => ('el, 'el, 'el, 'el, 'el, 'el, 'el, t('el));

include MutableArrayCore;

include FeatureMutableSyntax.Add({
  include MutableArrayCore;
  let length = Caml.Array.length;
  let get = Caml.Array.get;
  let set = Caml.Array.set;
});

include FeatureSequence.Add(MutableArrayCore);

let length = Caml.Array.length;
let isEmpty = arr => length(arr) === 0;

let getFirst = arr => Syntax.(arr[0]);
let getFirstExn = arr => SyntaxExn.(arr[0]);
let getIndex = (i, arr) => Syntax.(arr[i]);
let getIndexExn = (i, arr) => SyntaxExn.(arr[i]);
let getLast = arr => Syntax.(arr[length(arr) - 1]);
let getLastExn = arr => SyntaxExn.(arr[length(arr) - 1]);

let concat = (arrFirst, arrLast) => {
  open SyntaxExn;
  let nFirst = length(arrFirst);
  let nLast = length(arrLast);
  init(nFirst + nLast, i => i < nFirst ? arrFirst[i] : arrLast[i - nFirst]);
};

let addFirst = (el, arr) => concat([|el|], arr);
let addLast = (el, arr) => concat(arr, [|el|]);

let getFirstNExn = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    raise(
      Exceptions.IndexOutOfBounds("MutableArray.getFirstNExn", n, 0, len + 1),
    );
  } else {
    init(n, i => SyntaxExn.(arr[i]));
  };
};

let getFirstN = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    None;
  } else {
    Some(getFirstNExn(n, arr));
  };
};

let getLastNExn = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    raise(
      Exceptions.IndexOutOfBounds("MutableArray.getLastNExn", n, 0, len + 1),
    );
  } else {
    init(n, i => SyntaxExn.(arr[len + i - n]));
  };
};

let getLastN = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    None;
  } else {
    Some(getLastNExn(n, arr));
  };
};

let removeFirstNExn = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    raise(
      Exceptions.IndexOutOfBounds(
        "MutableArray.removeFirstNExn",
        n,
        0,
        len + 1,
      ),
    );
  } else {
    init(len - n, i => SyntaxExn.(arr[n + i]));
  };
};

let removeFirstN = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    None;
  } else {
    Some(removeFirstNExn(n, arr));
  };
};

let removeFirst = arr => removeFirstN(1, arr);

let removeFirstExn = arr => removeFirstNExn(1, arr);

let removeLastNExn = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    raise(
      Exceptions.IndexOutOfBounds(
        "MutableArray.removeLastNExn",
        n,
        0,
        len + 1,
      ),
    );
  } else {
    init(len - n, i => SyntaxExn.(arr[i]));
  };
};

let removeLastN = (n, arr) => {
  let len = length(arr);
  if (n < 0 || n > len) {
    None;
  } else {
    Some(removeLastNExn(n, arr));
  };
};

let removeLast = arr => removeLastN(1, arr);

let removeLastExn = arr => removeLastNExn(1, arr);

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

let flatten = arrOfArr => {
  open SyntaxExn;
  let lengths = map(length, arrOfArr);
  let sum = reduce((sum, x) => sum + x, 0, lengths);
  let arr = ref(0);
  let i = ref(0);
  init(
    sum,
    _ => {
      while (i^ >= lengths[arr^]) {
        incr(arr);
        i := 0;
      };
      let value = arrOfArr[arr^][i^];
      incr(i);
      value;
    },
  );
};

let match1 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 1) {
    None;
  } else {
    Some((arr[0], removeFirstNExn(1, arr)));
  };
};

let match2 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 2) {
    None;
  } else {
    Some((arr[0], arr[1], removeFirstNExn(2, arr)));
  };
};

let match3 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 3) {
    None;
  } else {
    Some((arr[0], arr[1], arr[2], removeFirstNExn(3, arr)));
  };
};

let match4 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 4) {
    None;
  } else {
    Some((arr[0], arr[1], arr[2], arr[3], removeFirstNExn(4, arr)));
  };
};

let match5 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 5) {
    None;
  } else {
    Some((arr[0], arr[1], arr[2], arr[3], arr[4], removeFirstNExn(5, arr)));
  };
};

let match6 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 6) {
    None;
  } else {
    Some((
      arr[0],
      arr[1],
      arr[2],
      arr[3],
      arr[4],
      arr[5],
      removeFirstNExn(6, arr),
    ));
  };
};

let match7 = arr => {
  open SyntaxExn;
  let n = length(arr);
  if (n < 7) {
    None;
  } else {
    Some((
      arr[0],
      arr[1],
      arr[2],
      arr[3],
      arr[4],
      arr[5],
      arr[6],
      removeFirstNExn(7, arr),
    ));
  };
};

let match1Exn = arr => SyntaxExn.(arr[0], removeFirstNExn(1, arr));

let match2Exn = arr => SyntaxExn.(arr[0], arr[1], removeFirstNExn(2, arr));

let match3Exn = arr =>
  SyntaxExn.(arr[0], arr[1], arr[2], removeFirstNExn(3, arr));

let match4Exn = arr =>
  SyntaxExn.(arr[0], arr[1], arr[2], arr[3], removeFirstNExn(4, arr));

let match5Exn = arr =>
  SyntaxExn.(
    arr[0],
    arr[1],
    arr[2],
    arr[3],
    arr[4],
    removeFirstNExn(5, arr),
  );

let match6Exn = arr =>
  SyntaxExn.(
    arr[0],
    arr[1],
    arr[2],
    arr[3],
    arr[4],
    arr[5],
    removeFirstNExn(6, arr),
  );

let match7Exn = arr =>
  SyntaxExn.(
    arr[0],
    arr[1],
    arr[2],
    arr[3],
    arr[4],
    arr[5],
    arr[6],
    removeFirstNExn(7, arr),
  );

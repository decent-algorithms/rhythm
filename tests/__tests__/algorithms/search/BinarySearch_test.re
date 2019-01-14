open TestFramework;

open Rhythm;

describe("BinarySearch", ({test}) => {
  ();
  test("simple array", ({expect}) => {
    let arr = [|5, 10, 15, 20, 25, 35, 1000|];
    let get = i => MutableArray.SyntaxExn.(arr[i]);
    let compare = (a: int, b: int) => a - b;
    let testCompare = value => compare(value, 35);
    let first = 0;
    let last = MutableArray.length(arr) - 1;
    let i =
      BinarySearch.searchi(~get, ~compare, ~testCompare, ~first, ~last, ());
    let i = Option.getExn(i);
    expect.int(i).toBe(5);
  });
});

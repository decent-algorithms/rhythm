open TestFramework;
open Rhythm;

describe("CamlArray", ({describe, test}) => {
  module FeatureFrontTests = FeatureFrontTests.Add(CamlArray);
  FeatureFrontTests.register(describe);

  module FeatureBackTests = FeatureBackTests.Add(CamlArray);
  FeatureBackTests.register(describe);

  module FeatureIndexedTests = FeatureIndexedTests.Add(CamlArray);
  FeatureIndexedTests.register(describe);

  module FeatureMutableIndexedTests = FeatureMutableIndexedTests.Add(CamlArray);
  FeatureMutableIndexedTests.register(describe);

  test("Syntax", ({expect}) => {
    let arr = [|0, 1, 2, 3, 4|];
    /* This is an error, because an Array syntax has not been opened. */
    /* let one = arr[1]; */
    let _ = arr;
    /*
     * A standard, safe syntax for accessing into an array.
     */
    open CamlArray.Syntax;
    let arr = [|0, 1, 2, 3, 4|];
    let one = arr[1] |> Option.getExn;
    expect.int(one).toBe(1);
    let _ = arr[1] = 100;
    let one = arr[1] |> Option.getExn;
    expect.int(one).toBe(100);
    /*
     * The nested syntax accepts an optional array as input so that deeply
     * nested arrays can still be easily accessed.
     */
    open CamlArray.SyntaxNested;
    let arr = [|0, 1, 2, 3, 4|];
    let arr = [|arr, arr, arr, arr, arr|];
    let arr = [|arr, arr, arr, arr, arr|];
    let arr = Some(arr);
    let one = arr[4][2][1] |> Option.getExn;
    expect.int(one).toBe(1);
    let _ = arr[4][2][1] = 100;
    let one = arr[4][2][1] |> Option.getExn;
    expect.int(one).toBe(100);
    /*
     * This is the standard array syntax that is unsafe and can throw
     * exceptions when given invalid indices.
     */
    open CamlArray.SyntaxExn;
    let arr = [|0, 1, 2, 3, 4|];
    let arr = [|arr, arr, arr, arr, arr|];
    let one = arr[2][1];
    expect.int(one).toBe(1);
    let () = arr[2][1] = 100;
    let one = arr[2][1];
    expect.int(one).toBe(100);
    /* When the index is too big an exception is thrown. */
    expect.fn(() => arr[1000]).toThrow();
    /*
     * Because it may be recommended to open modules to enable syntax we
     * provide a module to reset syntax that was opened.
     */
    open CamlArray.SyntaxReset;
    let arr = [|0, 1, 2, 3, 4|];
    /* This is an error, because we reset the Array syntax. */
    /* let one = arr[1]; */
    let _ = arr;
    ();
  });

  test("match functions", ({expect}) => {
    let arr = [|0, 1, 2, 3, 4|];
    let result =
      switch (CamlArray.match2(arr)) {
      | Some((0, 1, rest)) => true
      | _ => false
      };
    expect.bool(result).toBeTrue();

    let arr = [|0, 1, 2, 3, 4|];
    let result =
      switch (CamlArray.match5(arr)) {
      | Some((0, 1, 2, 3, 4, rest)) => true
      | _ => false
      };
    expect.bool(result).toBeTrue();

    let arr = [|0, 1, 2, 3, 4|];
    let result =
      switch (CamlArray.match6(arr)) {
      | Some((0, 1, 2, 3, 4, 5, rest)) => true
      | _ => false
      };
    expect.bool(result).toBeFalse();

    let arr = [|0, 1, 2, 3, 4|];
    let result =
      switch (CamlArray.match2Exn(arr)) {
      | (0, 1, rest) => true
      | _ => false
      };
    expect.bool(result).toBeTrue();

    let arr = [|0, 1, 2, 3, 4|];
    let result =
      switch (CamlArray.match5Exn(arr)) {
      | (0, 1, 2, 3, 4, rest) => true
      | _ => false
      };
    expect.bool(result).toBeTrue();
  });
});

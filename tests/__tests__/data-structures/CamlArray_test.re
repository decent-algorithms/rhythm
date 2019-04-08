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

  module FeatureMutableSyntaxTests = FeatureMutableSyntaxTests.Add(CamlArray);
  FeatureMutableSyntaxTests.register(describe);

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

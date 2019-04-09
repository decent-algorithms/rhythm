open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include
    FeatureFrontCommon.Interface with type tFrontCommon('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe =>
    describe("FeatureFrontCommon", ({test}) => {
      test("getFirst", ({expect}) => {
        let none = (-1);
        let getFirst = list =>
          list
          |> DS.fromCamlList
          |> DS.getFirst
          |> Option.getWithDefault(none);
        /* Examples */
        expect.int(getFirst([1, 2, 3, 4])).toBe(1);
        expect.int(getFirst([])).toBe(none);
        /* Additional tests */
        expect.int(getFirst([1])).toBe(1);
      });

      test("getFirstExn", ({expect}) => {
        let getFirstExn = list => list |> DS.fromCamlList |> DS.getFirstExn;
        /* Examples */
        expect.int(getFirstExn([1, 2, 3, 4])).toBe(1);
        expect.fn(() => getFirstExn([])).toThrow();
        /* Additional tests */
        expect.int(getFirstExn([1])).toBe(1);
      });

      test("getFirstN", ({expect}) => {
        let none = [(-1)];
        let getFirstN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.getFirstN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(getFirstN(2, [1, 2, 3, 4])).toEqual([1, 2]);
        expect.list(getFirstN(1, [1, 2, 3, 4])).toEqual([1]);
        expect.list(getFirstN(0, [])).toEqual([]);
        expect.list(getFirstN(1000, [1, 2])).toEqual(none);
        expect.list(getFirstN(1, [])).toEqual(none);
      });

      test("getFirstNExn", ({expect}) => {
        let getFirstNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.getFirstNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(getFirstNExn(2, [1, 2, 3, 4])).toEqual([1, 2]);
        expect.list(getFirstNExn(1, [1, 2, 3, 4])).toEqual([1]);
        expect.list(getFirstNExn(0, [])).toEqual([]);
        expect.fn(() => getFirstNExn(1000, [1, 2])).toThrow();
        expect.fn(() => getFirstNExn(1, [])).toThrow();
      });

      test("dropFirst", ({expect}) => {
        let none = [(-1)];
        let dropFirst = list =>
          list
          |> DS.fromCamlList
          |> DS.dropFirst
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(dropFirst([1, 2, 3])).toEqual([2, 3]);
        expect.list(dropFirst([])).toEqual(none);
      });

      test("dropFirstExn", ({expect}) => {
        let dropFirstExn = list =>
          list |> DS.fromCamlList |> DS.dropFirstExn |> DS.toCamlList;
        /* Examples */
        expect.list(dropFirstExn([1, 2, 3])).toEqual([2, 3]);
        expect.fn(() => dropFirstExn([])).toThrow();
      });

      test("dropFirstN", ({expect}) => {
        let none = [(-1)];
        let dropFirstN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.dropFirstN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(dropFirstN(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(dropFirstN(2, [1, 2, 3])).toEqual([3]);
        expect.list(dropFirstN(0, [])).toEqual([]);
        expect.list(dropFirstN(1000, [1, 2, 3])).toEqual(none);
        expect.list(dropFirstN(1, [])).toEqual(none);
      });

      test("dropFirstNExn", ({expect}) => {
        let dropFirstNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.dropFirstNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(dropFirstNExn(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(dropFirstNExn(2, [1, 2, 3])).toEqual([3]);
        expect.list(dropFirstNExn(0, [])).toEqual([]);
        expect.fn(() => dropFirstNExn(1000, [1, 2, 3])).toThrow();
        expect.fn(() => dropFirstNExn(1, [])).toThrow();
      });

      test("match functions", ({expect}) => {
        let ds = DS.fromCamlList([0, 1, 2, 3, 4]);
        let result =
          switch (DS.match2(ds)) {
          | Some((0, 1, rest)) => true
          | _ => false
          };
        expect.bool(result).toBeTrue();

        let result =
          switch (DS.match5(ds)) {
          | Some((0, 1, 2, 3, 4, rest)) => true
          | _ => false
          };
        expect.bool(result).toBeTrue();

        let result =
          switch (DS.match6(ds)) {
          | Some((0, 1, 2, 3, 4, 5, rest)) => true
          | _ => false
          };
        expect.bool(result).toBeFalse();

        let result =
          switch (DS.match2Exn(ds)) {
          | (0, 1, rest) => true
          | _ => false
          };
        expect.bool(result).toBeTrue();

        let result =
          switch (DS.match5Exn(ds)) {
          | (0, 1, 2, 3, 4, rest) => true
          | _ => false
          };
        expect.bool(result).toBeTrue();
      });
    });
};

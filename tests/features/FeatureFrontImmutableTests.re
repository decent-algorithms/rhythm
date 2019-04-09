open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include
    FeatureFrontImmutable.Interface with type tFrontImmutable('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe => {
    module FeatureFrontCommonTests = FeatureFrontCommonTests.Add(DS);
    FeatureFrontCommonTests.register(describe);

    describe("FeatureFrontImmutable", ({test}) => {
      test("Basic usage", ({expect}) => {
        let ds = DS.fromCamlList([]);
        expect.fn(() => DS.getFirstExn(ds)).toThrow();
        let ds = DS.addFirst(1, ds);
        expect.int(DS.getFirstExn(ds)).toBe(1);
        let ds = DS.addFirst(2, ds);
        expect.int(DS.getFirstExn(ds)).toBe(2);
        let ds = DS.addFirst(3, ds);
        expect.int(DS.getFirstExn(ds)).toBe(3);
        let ds = DS.addFirst(4, ds);
        expect.int(DS.getFirstExn(ds)).toBe(4);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(3);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(2);
        let ds = DS.removeFirstExn(ds);
        expect.int(DS.getFirstExn(ds)).toBe(1);
      });

      test("addFirst", ({expect}) => {
        let addFirst = (el, list) =>
          list |> DS.fromCamlList |> DS.addFirst(el) |> DS.toCamlList;
        /* Examples */
        expect.list(addFirst(9, [1, 2, 3])).toEqual([9, 1, 2, 3]);
        expect.list(addFirst(9, [])).toEqual([9]);
      });

      test("removeFirst", ({expect}) => {
        let none = [(-1)];
        let removeFirst = list =>
          list
          |> DS.fromCamlList
          |> DS.removeFirst
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirst([1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirst([])).toEqual(none);
      });

      test("removeFirstExn", ({expect}) => {
        let removeFirstExn = list =>
          list |> DS.fromCamlList |> DS.removeFirstExn |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstExn([1, 2, 3])).toEqual([2, 3]);
        expect.fn(() => removeFirstExn([])).toThrow();
      });

      test("removeFirstN", ({expect}) => {
        let none = [(-1)];
        let removeFirstN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.removeFirstN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstN(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirstN(2, [1, 2, 3])).toEqual([3]);
        expect.list(removeFirstN(0, [])).toEqual([]);
        expect.list(removeFirstN(1000, [1, 2, 3])).toEqual(none);
        expect.list(removeFirstN(1, [])).toEqual(none);
      });

      test("removeFirstNExn", ({expect}) => {
        let removeFirstNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.removeFirstNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(removeFirstNExn(1, [1, 2, 3])).toEqual([2, 3]);
        expect.list(removeFirstNExn(2, [1, 2, 3])).toEqual([3]);
        expect.list(removeFirstNExn(0, [])).toEqual([]);
        expect.fn(() => removeFirstNExn(1000, [1, 2, 3])).toThrow();
        expect.fn(() => removeFirstNExn(1, [])).toThrow();
      });

      test("updateFirst", ({expect}) => {
        let none = [(-1)];
        let updateFirst = (fn, list) =>
          list
          |> DS.fromCamlList
          |> DS.updateFirst(fn)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(updateFirst(x => x + 1, [1, 2, 3])).toEqual([2, 2, 3]);
        expect.list(updateFirst(x => x + 1, [])).toEqual(none);
      });

      test("updateFirstExn", ({expect}) => {
        let updateFirstExn = (fn, list) =>
          list |> DS.fromCamlList |> DS.updateFirstExn(fn) |> DS.toCamlList;
        /* Examples */
        expect.list(updateFirstExn(x => x + 1, [1, 2, 3])).toEqual([
          2,
          2,
          3,
        ]);
        expect.fn(() => updateFirstExn(x => x + 1, [])).toThrow();
      });
    });
  };
};

open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include FeatureIndexed.Interface with type tIndexed('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe =>
    describe("FeatureIndexed", ({test}) => {
      test("getIndex", ({expect}) => {
        let none = (-1);
        let getIndex = (i, list) =>
          list
          |> DS.fromCamlList
          |> DS.getIndex(i)
          |> Option.getWithDefault(none);
        /* Examples */
        expect.int(getIndex(0, [0, 1, 2, 3, 4])).toBe(0);
        expect.int(getIndex(2, [0, 1, 2, 3, 4])).toBe(2);
        expect.int(getIndex(-1, [0, 1, 2, 3, 4])).toBe(none);
        expect.int(getIndex(10, [0, 1, 2, 3, 4])).toBe(none);
        expect.int(getIndex(0, [])).toBe(none);
        /* Additional tests */
        expect.int(getIndex(4, [0, 1, 2, 3, 4])).toBe(4);
      });

      test("getIndexExn", ({expect}) => {
        let getIndexExn = (i, list) =>
          list |> DS.fromCamlList |> DS.getIndexExn(i);
        /* Examples */
        expect.int(getIndexExn(0, [0, 1, 2, 3, 4])).toBe(0);
        expect.int(getIndexExn(2, [0, 1, 2, 3, 4])).toBe(2);
        expect.fn(() => getIndexExn(-1, [0, 1, 2, 3, 4])).toThrow();
        expect.fn(() => getIndexExn(10, [0, 1, 2, 3, 4])).toThrow();
        expect.fn(() => getIndexExn(0, [])).toThrow();
        /* Additional tests */
        expect.int(getIndexExn(4, [0, 1, 2, 3, 4])).toBe(4);
      });
    });
};

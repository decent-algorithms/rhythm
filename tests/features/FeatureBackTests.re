open Rhythm;

module type DS = {
  type t('el);
  let toOCamlList: t('el) => list('el);
  let fromOCamlList: list('el) => t('el);
  include FeatureBack.Interface with type tBack('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe =>
    describe("FeatureBack", ({test}) => {
      test("getLast", ({expect}) => {
        let none = (-1);
        let getLast = list =>
          list
          |> DS.fromOCamlList
          |> DS.getLast
          |> Option.getWithDefault(none);
        /* Examples */
        expect.int(getLast([1, 2, 3, 4])).toBe(4);
        expect.int(getLast([])).toBe(none);
        /* Additional tests */
        expect.int(getLast([1])).toBe(1);
      });

      test("getLastExn", ({expect}) => {
        let getLastExn = list => list |> DS.fromOCamlList |> DS.getLastExn;
        /* Examples */
        expect.int(getLastExn([1, 2, 3, 4])).toBe(4);
        expect.fn(() => getLastExn([])).toThrow();
        /* Additional tests */
        expect.int(getLastExn([1])).toBe(1);
      });

      test("getLastN", ({expect}) => {
        let none = [(-1)];
        let getLastN = (n, list) =>
          list
          |> DS.fromOCamlList
          |> DS.getLastN(n)
          |> Option.getWithDefault(DS.fromOCamlList(none))
          |> DS.toOCamlList;
        /* Examples */
        expect.list(getLastN(2, [1, 2, 3, 4])).toEqual([3, 4]);
        expect.list(getLastN(1, [1, 2, 3, 4])).toEqual([4]);
        expect.list(getLastN(0, [])).toEqual([]);
        expect.list(getLastN(1000, [1, 2])).toEqual(none);
        expect.list(getLastN(1, [])).toEqual(none);
      });

      test("getLastNExn", ({expect}) => {
        let getLastNExn = (n, list) =>
          list |> DS.fromOCamlList |> DS.getLastNExn(n) |> DS.toOCamlList;
        /* Examples */
        expect.list(getLastNExn(2, [1, 2, 3, 4])).toEqual([3, 4]);
        expect.list(getLastNExn(1, [1, 2, 3, 4])).toEqual([4]);
        expect.list(getLastNExn(0, [])).toEqual([]);
        expect.fn(() => getLastNExn(1000, [1, 2])).toThrow();
        expect.fn(() => getLastNExn(1, [])).toThrow();
      });

      test("addLast", ({expect}) => {
        let addLast = (el, list) =>
          list |> DS.fromOCamlList |> DS.addLast(el) |> DS.toOCamlList;
        /* Examples */
        expect.list(addLast(9, [1, 2, 3])).toEqual([1, 2, 3, 9]);
        expect.list(addLast(9, [])).toEqual([9]);
      });

      test("removeLast", ({expect}) => {
        let none = [(-1)];
        let removeLast = list =>
          list
          |> DS.fromOCamlList
          |> DS.removeLast
          |> Option.getWithDefault(DS.fromOCamlList(none))
          |> DS.toOCamlList;
        /* Examples */
        expect.list(removeLast([1, 2, 3])).toEqual([1, 2]);
        expect.list(removeLast([])).toEqual(none);
      });

      test("removeLastExn", ({expect}) => {
        let removeLastExn = list =>
          list |> DS.fromOCamlList |> DS.removeLastExn |> DS.toOCamlList;
        /* Examples */
        expect.list(removeLastExn([1, 2, 3])).toEqual([1, 2]);
        expect.fn(() => removeLastExn([])).toThrow();
      });

      test("removeLastN", ({expect}) => {
        let none = [(-1)];
        let removeLastN = (n, list) =>
          list
          |> DS.fromOCamlList
          |> DS.removeLastN(n)
          |> Option.getWithDefault(DS.fromOCamlList(none))
          |> DS.toOCamlList;
        /* Examples */
        expect.list(removeLastN(1, [1, 2, 3])).toEqual([1, 2]);
        expect.list(removeLastN(2, [1, 2, 3])).toEqual([1]);
        expect.list(removeLastN(0, [])).toEqual([]);
        expect.list(removeLastN(1000, [1, 2, 3])).toEqual(none);
        expect.list(removeLastN(1, [])).toEqual(none);
      });

      test("removeLastNExn", ({expect}) => {
        let removeLastNExn = (n, list) =>
          list |> DS.fromOCamlList |> DS.removeLastNExn(n) |> DS.toOCamlList;
        /* Examples */
        expect.list(removeLastNExn(1, [1, 2, 3])).toEqual([1, 2]);
        expect.list(removeLastNExn(2, [1, 2, 3])).toEqual([1]);
        expect.list(removeLastNExn(0, [])).toEqual([]);
        expect.fn(() => removeLastNExn(1000, [1, 2, 3])).toThrow();
        expect.fn(() => removeLastNExn(1, [])).toThrow();
      });

      test("updateLast", ({expect}) => {
        let none = [(-1)];
        let updateLast = (fn, list) =>
          list
          |> DS.fromOCamlList
          |> DS.updateLast(fn)
          |> Option.getWithDefault(DS.fromOCamlList(none))
          |> DS.toOCamlList;
        /* Examples */
        expect.list(updateLast(x => x + 1, [1, 2, 3])).toEqual([1, 2, 4]);
        expect.list(updateLast(x => x + 1, [])).toEqual(none);
      });

      test("updateLastExn", ({expect}) => {
        let updateLastExn = (fn, list) =>
          list |> DS.fromOCamlList |> DS.updateLastExn(fn) |> DS.toOCamlList;
        /* Examples */
        expect.list(updateLastExn(x => x + 1, [1, 2, 3])).toEqual([
          1,
          2,
          4,
        ]);
        expect.fn(() => updateLastExn(x => x + 1, [])).toThrow();
      });
    });
};

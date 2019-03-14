open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include FeatureBack.Interface with type tBack('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;
  let register = describe =>
    describe("FeatureBack", ({test}) => {
      test("Basic usage", ({expect}) => {
        let ds = DS.fromCamlList([]);
        expect.fn(() => DS.getLastExn(ds)).toThrow();
        let ds = DS.addLast(1, ds);
        expect.int(DS.getLastExn(ds)).toBe(1);
        let ds = DS.addLast(2, ds);
        expect.int(DS.getLastExn(ds)).toBe(2);
        let ds = DS.addLast(3, ds);
        expect.int(DS.getLastExn(ds)).toBe(3);
        let ds = DS.addLast(4, ds);
        expect.int(DS.getLastExn(ds)).toBe(4);
        let ds = DS.removeLastExn(ds);
        expect.int(DS.getLastExn(ds)).toBe(3);
        let ds = DS.removeLastExn(ds);
        expect.int(DS.getLastExn(ds)).toBe(2);
        let ds = DS.removeLastExn(ds);
        expect.int(DS.getLastExn(ds)).toBe(1);
      });

      test("getLast", ({expect}) => {
        let none = (-1);
        let getLast = list =>
          list
          |> DS.fromCamlList
          |> DS.getLast
          |> Option.getWithDefault(none);
        /* Examples */
        expect.int(getLast([1, 2, 3, 4])).toBe(4);
        expect.int(getLast([])).toBe(none);
        /* Additional tests */
        expect.int(getLast([1])).toBe(1);
      });

      test("getLastExn", ({expect}) => {
        let getLastExn = list => list |> DS.fromCamlList |> DS.getLastExn;
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
          |> DS.fromCamlList
          |> DS.getLastN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(getLastN(2, [1, 2, 3, 4])).toEqual([3, 4]);
        expect.list(getLastN(1, [1, 2, 3, 4])).toEqual([4]);
        expect.list(getLastN(0, [])).toEqual([]);
        expect.list(getLastN(1000, [1, 2])).toEqual(none);
        expect.list(getLastN(1, [])).toEqual(none);
      });

      test("getLastNExn", ({expect}) => {
        let getLastNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.getLastNExn(n) |> DS.toCamlList;
        /* Examples */
        expect.list(getLastNExn(2, [1, 2, 3, 4])).toEqual([3, 4]);
        expect.list(getLastNExn(1, [1, 2, 3, 4])).toEqual([4]);
        expect.list(getLastNExn(0, [])).toEqual([]);
        expect.fn(() => getLastNExn(1000, [1, 2])).toThrow();
        expect.fn(() => getLastNExn(1, [])).toThrow();
      });

      test("addLast", ({expect}) => {
        let addLast = (el, list) =>
          list |> DS.fromCamlList |> DS.addLast(el) |> DS.toCamlList;
        /* Examples */
        expect.list(addLast(9, [1, 2, 3])).toEqual([1, 2, 3, 9]);
        expect.list(addLast(9, [])).toEqual([9]);
      });

      test("removeLast", ({expect}) => {
        let none = [(-1)];
        let removeLast = list =>
          list
          |> DS.fromCamlList
          |> DS.removeLast
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeLast([1, 2, 3])).toEqual([1, 2]);
        expect.list(removeLast([])).toEqual(none);
      });

      test("removeLastExn", ({expect}) => {
        let removeLastExn = list =>
          list |> DS.fromCamlList |> DS.removeLastExn |> DS.toCamlList;
        /* Examples */
        expect.list(removeLastExn([1, 2, 3])).toEqual([1, 2]);
        expect.fn(() => removeLastExn([])).toThrow();
      });

      test("removeLastN", ({expect}) => {
        let none = [(-1)];
        let removeLastN = (n, list) =>
          list
          |> DS.fromCamlList
          |> DS.removeLastN(n)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(removeLastN(1, [1, 2, 3])).toEqual([1, 2]);
        expect.list(removeLastN(2, [1, 2, 3])).toEqual([1]);
        expect.list(removeLastN(0, [])).toEqual([]);
        expect.list(removeLastN(1000, [1, 2, 3])).toEqual(none);
        expect.list(removeLastN(1, [])).toEqual(none);
      });

      test("removeLastNExn", ({expect}) => {
        let removeLastNExn = (n, list) =>
          list |> DS.fromCamlList |> DS.removeLastNExn(n) |> DS.toCamlList;
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
          |> DS.fromCamlList
          |> DS.updateLast(fn)
          |> Option.getWithDefault(DS.fromCamlList(none))
          |> DS.toCamlList;
        /* Examples */
        expect.list(updateLast(x => x + 1, [1, 2, 3])).toEqual([1, 2, 4]);
        expect.list(updateLast(x => x + 1, [])).toEqual(none);
      });

      test("updateLastExn", ({expect}) => {
        let updateLastExn = (fn, list) =>
          list |> DS.fromCamlList |> DS.updateLastExn(fn) |> DS.toCamlList;
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

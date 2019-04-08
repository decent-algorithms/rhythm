open Rhythm;

module type DS = {
  type t('el);
  let toCamlList: t('el) => list('el);
  let fromCamlList: list('el) => t('el);
  include
    FeatureMutableSyntax.Interface with type tMutableSyntax('el) = t('el);
};

module type Output = {let register: Rely.Describe.describeFn(_) => unit;};

module Add = (DS: DS) : Output => {
  open Rely.Describe;

  type setup('el) = {
    innerDS: ref(DS.t('el)),
    reset: unit => DS.t('el),
  };

  let setup = getList => {
    let innerDS = ref(DS.fromCamlList(getList()));
    let reset = () => {
      innerDS.contents = DS.fromCamlList(getList());
      innerDS.contents;
    };
    {innerDS, reset};
  };

  let register = describe =>
    describe("FeatureMutableSyntax", ({test}) => {
      test("syntax", ({expect}) => {
        let {reset} = setup(() => [0, 1, 2, 3, 4]);

        let ds = reset();
        /* This is an error, because an Array syntax has not been opened. */
        /* let one = ds[1]; */
        let _ = ds;
        /*
         * A standard, safe syntax for accessing into an array.
         */
        open DS.Syntax;
        let ds = reset();
        let one = ds[1] |> Option.getExn;
        expect.int(one).toBe(1);
        let _ = ds[1] = 100;
        let one = ds[1] |> Option.getExn;
        expect.int(one).toBe(100);
        /*
         * Because it may be recommended to open modules to enable syntax we
         * provide a module to reset syntax that was opened.
         */
        open DS.SyntaxReset;
        let ds = reset();
        /* This is an error, because we reset the Array syntax. */
        /* let one = ds[1]; */
        let _ = ds;
        ();
      });

      test("nested syntax", ({expect}) => {
        let nested = () => {
          let list = DS.fromCamlList([0, 1, 2, 3, 4]);
          let list = DS.fromCamlList([list, list, list, list, list]);
          [list, list, list, list, list];
        };
        let {reset} = setup(nested);
        /*
         * The nested syntax accepts an optional array as input so that deeply
         * nested arrays can still be easily accessed.
         */
        open DS.SyntaxNested;
        let ds = reset();
        let ds = Some(ds);
        let one = ds[4][2][1] |> Option.getExn;
        expect.int(one).toBe(1);
        let _ = ds[4][2][1] = 100;
        let one = ds[4][2][1] |> Option.getExn;
        expect.int(one).toBe(100);
        /*
         * This is the standard array syntax that is unsafe and can throw
         * exceptions when given invalid indices.
         */
        open DS.SyntaxExn;
        let ds = reset();
        let one = ds[4][2][1];
        expect.int(one).toBe(1);
        let () = ds[4][2][1] = 100;
        let one = ds[4][2][1];
        expect.int(one).toBe(100);
        /* When the index is too big an exception is thrown. */
        expect.fn(() => ds[1000]).toThrow();
      });
    });
};

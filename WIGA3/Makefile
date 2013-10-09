CC = ocamlc

main: lexer.cmo wig.cmo main.cmo tree.cmo
	ocamlc -o wig lexer.cmo wig.cmo main.cmo

tree.cmo: tree.ml
	ocamlc -c tree.ml

main.cmo: main.ml
	ocamlc -c main.ml

wig.cmo: wig.ml
	ocamlc -c wig.ml

lexer.cmo: lexer.ml
	ocamlc -c lexer.ml

wig.mli: wig.mly
	ocamlyacc wig.mly

wig.ml: wig.mli
	ocamlc -c wig.mli

lexer.ml: lexer.mll wig.cmo
	ocamllex lexer.mll

clean:
	rm lexer.cm*; rm wig.cm*; rm main.cm*; rm *.mli



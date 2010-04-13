.PHONY=main clean clean_all


# Construye el informe


informe.pdf: informe.tex
#	latex -interaction=batchmode informe.tex
	pdflatex -interaction=batchmode informe.tex
	
clean:
	rm -f *.toc *.out *.aux *.log *~
	
clean_all: clean
	rm -f informe.pdf

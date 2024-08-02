.PHONY: reference
reference:
	python3 TeamReference/team_reference.py && pdflatex TeamReference/team_reference.tex

.PHONY: parse
parse:
	python3 parse/parse.py

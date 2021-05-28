.PHONY: clean clean-ipynb clean-pyc clean-build docs help upgrade
.DEFAULT_GOAL := help

define PRINT_HELP_PYSCRIPT
import re, sys

for line in sys.stdin:
	match = re.match(r'^([a-zA-Z_-]+):.*?## (.*)$$', line)
	if match:
		target, help = match.groups()
		print("%-20s %s" % (target, help))
endef
export PRINT_HELP_PYSCRIPT

BROWSER := python -c "$$BROWSER_PYSCRIPT"

help:
	@python -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

docs: ## Build book
	jupyter-book build book
	for folder in cpp git optimization python stochastic_processes testing_codestyle summary; do \
    	cp -r book/docs/lectures/$$folder/fig book/_build/html/docs/lectures/$$folder/ ; \
	done
	cp -r book/docs/info/fig book/_build/html/docs/info/
	touch book/_build/html/.nojekyll
	

show:  ## Open index page
	open book/_build/html/index.html

clean: clean-build clean-pyc clean-ipynb ## remove all build, test, coverage and Python artifacts

gh-pages-deploy: docs  ## Deploy to github pages
	git checkout gh-pages
	git add -f book/_build/html && git commit -m "Add html docs"
	git subtree push --prefix book/_build/html origin gh-pages
	git checkout master

clean-build: ## remove build artifacts
	rm -fr book/_build/

clean-pyc: ## remove Python file artifacts
	find . -name '*.pyc' -exec rm -f {} +
	find . -name '*.pyo' -exec rm -f {} +
	find . -name '*~' -exec rm -f {} +
	find . -name '__pycache__' -exec rm -fr {} +

clean-ipynb:  ## remove notebook artifacts
	find . -name '.ipynb_checkpoints' -exec rm -fr {} +

clean-pytest:  ## remove pytest cache
	find . -name '.pytest_cache' -exec rm -fr {} +


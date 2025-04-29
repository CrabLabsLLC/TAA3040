import os, sys
sys.path.insert(0, os.path.abspath('../src'))

project   = 'TAA3040 Driver'
author    = 'Orion Serup'
release   = '0.1'

extensions = [
    'sphinx.ext.graphviz',  # embed .dot graphs
    'breathe',              # pull Doxy XML
    'exhale',               # generate API rst
    'sphinx.ext.intersphinx',
]

# Breathe
breathe_projects = {
    "TAA3040": "xml"
}
breathe_default_project = "TAA3040"

# Exhale — where to put the auto API docs
exhale_args = {
    # folder for generated rst
    "containmentFolder":   "./api",
    # root toctree file
    "rootFileName":        "modules.rst",
    # title for the API root page
    "rootFileTitle":       "API Reference",
    # breathe project name
    "doxygenStripFromPath": "..",
    "createTreeView":      True,
}

# Intersphinx (e.g. link to C standard docs, if you like)
intersphinx_mapping = {
    'c': ('https://en.cppreference.com/w/', None)
}

# HTML theme
html_theme = 'alabaster'
html_theme_options = {
    'description': 'High‐performance audio ADC driver',
    'show_related': True,
    'sidebar_width': '220px',
}

# Graphviz output format
graphviz_output_format = 'svg'

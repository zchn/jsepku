(TeX-add-style-hook "intro"
 (lambda ()
    (TeX-add-symbols
     "keyword"
     "remark")
    (TeX-run-style-hooks
     "xcolor"
     "listings"
     "zhfontcfg"
     "latex2e"
     "art12"
     "article"
     "12pt"
     "a4paper")))


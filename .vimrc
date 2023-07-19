let s:tab_sizes = { 'nix': 2 }
let s:default_tab_size = 4

function s:set_shift_width(filetype)
    exec 'set shiftwidth='.get(s:tab_sizes, a:filetype, s:default_tab_size)
endfunction

autocmd FileType * call s:set_shift_width(expand('<amatch>'))


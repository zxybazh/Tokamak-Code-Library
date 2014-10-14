sy on
set nu
set ruler
map <F2> :w<cr>
map <F4> :q<cr>
set cindent
set st=4
set ts=4
set sw=4
set smartindent
set si
map <F9> :set makeprg=g++\ %\ -o\ %<\ -g\ -Wall<CR>:silent make<CR>:copen<CR>:redraw!<CR>

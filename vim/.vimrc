" 打开文件类型检测
filetype on

" 取消强制vi模式
set nocompatible

" 设置语法颜色
set background=dark

colorscheme solarized

let g:solarized_termcolors=256

hi Comment ctermfg=241

" 设置行号
set number

" 设置自动缩进
set autoindent

" 打开语法高亮
syntax on

" 制表符占4空格
set tabstop=4

" 默认缩进占4个空格
set shiftwidth=4

" 搜索模式里忽略大小写
set ignorecase

" 如果搜索模式里面包含大小字符，则不使用ignorecase选项
set smartcase

" 显示输入的命令
set showcmd

" 高亮当前选中行
set cursorline

" 设置vim刷新时间（默认500ms）,同时这也是tagbar动态高亮显示刷新的时间
set updatetime=100

" Specify a directory for plugins

call plug#begin('~/.vim/plugged')

" NERDTree
Plug 'scrooloose/nerdtree'

" airline
Plug 'vim-airline/vim-airline'

" airline主题
Plug 'vim-airline/vim-airline-themes'

" YCM代码补全
Plug 'valloric/youcompleteme'

" Tarbar
Plug 'majutsushi/tagbar'

" NERD-Commenter
Plug 'scrooloose/nerdcommenter'

" Auto Piars 自动补全括号
Plug 'jiangmiao/auto-pairs'


call plug#end()

""""""""""""""""""""全局按键映射""""""""""""""""""""
" 设置<leader>键
let mapleader=','


""""""""""""""""""""NERDTree""""""""""""""""""""
" 设置nerdtree按键映射
nmap <F2> :NERDTreeToggle<CR>

"打开文件自动 打开tagbar
autocmd BufReadPost *.cpp,*.c,*.h,*.hpp,*.cc,*.cxx call tagbar#autoopen()  

""""""""""""""""""""NERDTree""""""""""""""""""""
" F3打开开tagbar
nmap <F3> :TagbarToggle<CR>
" 当最后一个buffer关闭时，自动退出nerdtree
autocmd BufEnter * if (winnr("$") == 1 && exists("b:NERDTree") && b:NERDTree.isTabTree()) | q | endif


"autocmd BufEnter * if 0 == len(filter(range(1, winnr('$')), 'empty(getbufvar(winbufnr(v:val), "&bt"))')) | qa! | endif



 """""""""""""""""""vim-airline""""""""""""""""""""
" 开启buffer栏，默认是关闭的
let g:airline#extensions#tabline#enabled=1
" 设置"<leader> + n"切换到下一个buffer 
nmap <leader>n :bn<CR>
" 设置"<leader> + p" 切换到上一个buffer
nmap <leader>p :bp<CR>


" 使用powerline-font
let g:airline_powerline_fonts = 1


"""""""""""""""""""YCM"""""""""""""""""""
let g:ycm_global_ycm_extra_conf='~/.vim/.ycm_extra_conf.py'


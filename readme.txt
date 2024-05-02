git filter-branch --commit-filter '
        if [ "$GIT_AUTHOR_NAME" = "xx•xx" ];
        then
                export GIT_AUTHOR_NAME="神圣•凯莎";
                export GIT_AUTHOR_EMAIL="kaisha@gmail.com";
        fi;
        git commit-tree "$@";
' --tag-name-filter cat -- --branches --tags

git push --force origin main
# Git命令

## reset
git reset是将之前的提交记录全部抹去，将 HEAD 指向自己重置的提交记录，对应的提交记录都不复存在

### 方法1
重置当前分支到提交点：git reset --hard

强制推送到远程分支：git push -f

### 方法1
重置当前分支到提交点：git reset --hard

远程分支提交点，重置当前分支到提交点：git reset --soft

推送到远程分支：git push

新增一个提交，本质是在新的提交里文件做相反操作，已达成重置效果。

## revert
git revert是用来重做某一个 commit 提交的内容，在我们原始的提交之中，我们会发现分支上面有创建了一个新的 commit 提交，而此时我们对于想重做的某个 commit 提交的内容都不存在了。

git revert命令重做操作
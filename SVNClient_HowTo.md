# Introduction #

> 簡介兩種Windows上可以使用的Subversion Client端：分別是圖形介面的[TortoiseSVN](http://tortoisesvn.net/)，或者是文字模式的[CollabNet Subversion Client](http://www.collab.net/downloads/subversion/)

# Get Started #
> 建議先取得Subversion Client所需的[密碼](https://code.google.com/hosting/settings)，此步驟需要登入Google Account

# TortoiseSVN　 #

> 用法請參考以下網頁
  * [用 Subversion 跟 Google Code 作版本控制 （一）→ 圖文教學](http://blog.ericsk.org/archives/446)
  * [用 Subversion 跟 Google Code 作版本控制 （二）→ 圖文教學](http://blog.ericsk.org/archives/447)

# CollabNetSVN Client #

> _這邊整理幾個比較常用的指令_

  * **svn checkout** URL`[@REV]`... `[PATH]` `[--username]` `[--password]`

> 將檔案自Repository取回Local，第一次使用時才做

> ex.svn checkout https://open-online-judge.googlecode.com/svn/ open-online-judge --username kevinhs1150@gmail.com

  * **svn update** `[PATH..]`

> 將Local端的檔案更新至最新的版本，每次工作之前一定要先做

  * **svn add** PATH...

> 將檔案加入設定檔中

  * **svn del** PATH `[--keep-local]`

> 將檔案自設定檔移除，建議使用keep-local，否則會將Local端檔案一併刪除

  * **svn status** `[PATH..]`

> 檢查檔案狀態，並查看是否衝突

　　幾個常見符號： M: Modification, A: Add, D: Delete, ?: Unknown, C: Conflict

  * **svn commit** `[PATH...]`　`[--message (-m) MESSAGE]`

　　上傳新的版本，輸入這次更動的摘要

> _每次的工作大致上的流程就是先檢查版本是否更新(update)，如果是第一次使用則是將檔案取回Local(check out)，將檔案自設定檔中加入或刪除(add/del)，檢查狀態(status)最後上傳(commit)_


> _詳細指令的用法可參考_
    * [SVN Book(Version Control with Subversion)](http://svnbook.red-bean.com/nightly/en/index.html)
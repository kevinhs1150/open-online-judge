<p><font size='16'><b>NOTE</b></font></p>
<p><font size='3'>New version of protocol in docx(Microsoft Word 2007/2010) format is uploaded and available at <a href='http://code.google.com/p/open-online-judge/downloads/list'>Downloads</a> section.</font></p>
<p><font size='3'>An updated version of protocol 0.2 is also there, which contains a more complete known problem listing.</font></p>

<br><br><br>

<h1>Protocol</h1>
<br>
<br>
<h1>Functionalities requiring network communication</h1>

<blockquote>server<br>
<blockquote>must cover all requirements below<br>
</blockquote>team<br>
<blockquote>submission<br>
clarification<br>
problem download<br>
scoreboard update (listen)<br>
runs result (listen)<br>
</blockquote>judge<br>
<blockquote>receive run request (listen)<br>
return run result<br>
problem update (listen)<br>
see clarification (listen)<br>
</blockquote>admin<br>
<blockquote>manage account<br>
manage problems<br>
manage contest site<br>
reply clarifications<br>
global broadcast<br>
set server property<br>
see server status(ping, bandwidth test) (implement with other tools)</blockquote></blockquote>

<h1>Usage instruction</h1>

Include your own header file and use the function inside to communicate.  The usage of functions should be rather easy and pretty well documented inside the header file, just read before use.<br>
<br>
All transmissions are done in UTF-8.  For the purpose of simplicity, the function will only take wide character argument.  So make sure to handle all strings or at least convert them into wchar_t<code>* type</code> before passing it to the library.<br>
<br>
For those who only want to use the library, this is all you need from this documentation.<br>
<br>
<h1>Detail - Basis</h1>
All packets will start with two bytes of fixed binary data.<br>
<br>
The first byte will indicate the packet source, defined as follows:<br>
<blockquote>server = 0 (the packet comes from server).<br>
admin = 1, judge = 2, team = 3.</blockquote>

This byte will be named SR in the following documentation. The second byte is a unique identification to identify the purpose of the packet.  This byte will be named ID in the following documentation. All communications are done with pure string separated by null character “\0” unless specified explicitly.<br>
<br>
<h1>Detail - Protocol definitions and diagrams</h1>

In the block diagram, <font color='red'> red </font> block means binary data.  The SRID column is the first two fixed bytes of data and will be prefixed before almost all messages. The <font color='blue'> blue </font> block means file transfer via VSFTP (Very Simple File Transfer Protocol) defined also in this document.<br>
<br>
<h2>VSFTP Protocol</h2>

<table><thead><th> file size </th><th> <font color='red'> file content </font> </th></thead><tbody></tbody></table>

This is a very, very simple file transfer protocol.  It will be used in the OOJ protocol for file transfer.<br>
<br>
<h2>Account Management</h2>

<b>Login</b> (SR = depend, ID = 00)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> account </th><th> password </th></thead><tbody></tbody></table>

Whether the login client is team, judge, admin will be determined from SR byte.<br>
<br>
<b>Login Confirmation</b> (SR = 0, ID = 00)<br>
<br>
<table><thead><th> <font color='red'> SRID </font>  </th><th> confirmation </th></thead><tbody></tbody></table>

If confirmation byte is 1, the account and password are valid.  If confirmation byte is 0, then the client program should block the user from proceeding.<br>
<br>
<b>Logout</b> (SR = depend, ID = 01)<br>
<br>
<table><thead><th> <font color='red'> SRID </font>  </th><th> account id </th></thead><tbody></tbody></table>

<b>Logout Confirmation</b> (SR = 0, ID = 01)<br>
<br>
<table><thead><th> <font color='red'> SRID </font>  </th><th> confirmation </th></thead><tbody></tbody></table>

Simply indicate that the server has received the logout request.  This message can be ignored by client. It is however suggested that the client should handle this reply properly.<br>
<br>
<h2>Team and Server</h2>

<b>Team -> Server, submission</b> (SR = 3, ID = 10)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> account id </th><th> problem id </th><th> coding language </th></thead><tbody>
<tr><td> <font color='blue'> source code file </font> </td></tr></tbody></table>

A source file transfer will happen following the submission request. Note that server should wait for the file transfer. In reply, server should send a run result notification, with result string telling the team that this problem is being judged.<br>
<br>
<b>Team -> Server, clarification</b> (SR = 3, ID = 11)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> account id </th><th>private </th><th> clarification message </th></thead><tbody></tbody></table>

The private byte will be enabled by 1 and disabled by 0. If it is enabled, the clarification will be marked <b>private</b> on admin client. If admin determines that this is a private message, the reply will not be broadcasted. In reply, server should send a clarification reply, with result string telling the team that this clarification is still being viewed by administrators.<br>
<br>
<br>
<b>Team -> Server, problem download</b> (SR = 3, ID = 12)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> account id </th><th> problem id </th></thead><tbody></tbody></table>

Server should reply with the problem requested instantly.<br>
<br>
<b>Server -> Team, run result</b> (SR = 0, ID = 10)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> run id </th><th> result string </th></thead><tbody></tbody></table>

<b>Server -> Team, clarification reply</b> (SR = 0, ID = 11)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> clar id </th><th> result string </th></thead><tbody></tbody></table>

<b>Server -> Team, scoreboard update</b> (SR = 0, ID = 12)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> updated team account id </th><th> new account </th><th> new accept counts </th><th> new time </th></thead><tbody></tbody></table>

The second parameter will be “the team needed updating”.  For example, if team 10 solved a problem, its new accept counts and time will be sent to all team clients, with second argument “10”.<br>
<br>
<b>Server -> Team, problem upload</b> (SR = 0, ID = 13)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th></thead><tbody>
<tr><td> <font color='blue'> problem content </font> </td></tr></tbody></table>

<h2>Judge and Server</h2>

<b>Judge -> Server, run result</b> (SR = 2, ID = 10)<br>
<br>
<table><thead><th> <font color='red'> SRID </font>  </th><th> run id </th><th> result string </th></thead><tbody></tbody></table>

The judge will not know the submitter.<br>
<br>
<b>Server -> Judge, run request</b> (SR = 0, ID = 14)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> run id </th><th> problem id </th><th> coding language </th></thead><tbody>
<tr><td> <font color='blue'> source code file </font> </td></tr></tbody></table>

<b>Server -> Judge, problem update</b> (SR = 0, ID = 15)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> problem id </th></thead><tbody>
<tr><td> <font color='blue'> problem description </font> </td><td> <font color='blue'> input data </font> </td><td> <font color='blue'> correct answer </font> </td></tr></tbody></table>

If the problem does not exist, the judge client should add a new problem entry.<br>
<br>
<h2>Admin and Server</h2>

<b>Admin -> Server, account management</b> (SR = 1, ID = 10)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> operation id </th><th> parameters </th></thead><tbody></tbody></table>

Operation id:<br>
<br>
<ol><li>add, parameters<br>
<blockquote><table><thead><th> type </th><th> account </th><th> password </th></thead><tbody>
</blockquote></li><li>delete, parameters<br>
<blockquote><tr><td> account </td><td> id </td></tr>
</blockquote></li><li>modify, parameters: no type change allowed<br>
<blockquote><tr><td> account id </td><td> new account </td><td> new password </td></tr>
</blockquote></li><li>update: no parameter.  Server sends all account information to requested administrator.</li></ol></tbody></table>

<b>Admin -> Server, problem management</b> (SR = 1, ID = 11)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> operation id </th><th> problem id </th><th> parameters </th></thead><tbody></tbody></table>

<blockquote>Operation id:</blockquote>

<ol><li>add<br>
<blockquote>parameters<br>
<table><thead><th> <font color='blue'> problem description </font> </th><th> <font color='blue'> input data </font> </th><th> <font color='blue'> correct answer </font> </th></thead><tbody>
</blockquote></li><li>delete: no parameter<br>
</li><li>modify<br>
<blockquote>parameters<br>
<tr><td> <font color='blue'> problem description </font> </td><td> <font color='blue'> input data </font> </td><td> <font color='blue'> correct answer </font> </td></tr>
</blockquote></li><li>update: no parameter.  Server sends all problem information to requested administrator.</li></ol></tbody></table>

<b>Admin -> Server, clarification reply</b> (SR = 1, ID = 12)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> clar id </th><th> private </th><th> result string </th></thead><tbody></tbody></table>

If private byte is set, this message will only be replied to its original requester.  Otherwise, regardless how the requester set its private byte, this message will be broadcasted to all contestants.<br>
<br>
<b>Admin -> Server, global broadcast</b> (SR = 1, ID = 12)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> 0 </th><th> 0 </th><th> broadcast message </th></thead><tbody></tbody></table>

Make use of clarification reply and fix clarification id.  Private status is also fixed to 0 for the message to be globally broadcasted.<br>
<br>
<b>Admin -> Server, property settings</b> (SR = 1, ID = 13)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th>     </th><th>     </th><th>               </th></thead><tbody></tbody></table>

<b>Server -> Admin, contest site situation</b> (SR = 0, ID = 16)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th>     </th><th>     </th><th>               </th></thead><tbody></tbody></table>

<b>Server -> Admin, clarification request</b> (SR = 0, ID = 17)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> clar id </th><th>private </th><th> clarification message </th></thead><tbody></tbody></table>

The administrator will not know the clarification requester.  The private byte is set according to how user specify it.<br>
<br>
<b>Server -> Admin, account information</b> (SR = 0, ID = 18)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> account id </th><th> account type </th><th> account </th></thead><tbody></tbody></table>

<b>Server -> Admin, problem information</b> (SR = 0, ID = 19)<br>
<br>
<table><thead><th> <font color='red'> SRID </font> </th><th> problem id </th></thead><tbody>
<tr><td> <font color='blue'> problem description </font> </td><td> <font color='blue'> input data </font> </td><td> <font color='blue'> correct answer </font> </td></tr></tbody></table>

<h1>Known Problem / Limitation</h1>

<ol><li>In administrator client, property setting and status monitoring is not yet defined.<br>
</li><li>Multiple judges may compete on the same run (race condition).  Solution: Mark the run as being judged when one judge takes over that run request.</li></ol>

<h1>Change Log</h1>

<i>version 0.1</i>

<blockquote>Initial version.</blockquote>

<i>version 0.2</i>

Implemented account ID.<br>
<br>
File transfer changed into a tiny protocol.  In the implementation, files will be transferred through another function rather than embedded into original message. Added two protocols to back transfer account information and problem information to administrator. (two proto added between admin and server)
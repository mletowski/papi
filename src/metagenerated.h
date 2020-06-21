/*  The metagrammar structure written as LisData object, 
    self-generated by metagrammar.dp and 
    converted to LisData C++ objects by json_LisData.dp
 */

LisData  metagenerated =

{"metagrammar.dp:1:1","Grammar",
{"metagrammar.dp:9:1","Production","info",
{"metagrammar.dp:9:8","Branch",
{"metagrammar.dp:9:8","Receipt",
{"metagrammar.dp:9:8","ElementCall","::input","$f"},
{"metagrammar.dp:9:19","ElementCall","::line","$line"},
{"metagrammar.dp:9:32","ElementCall","::column","$col"}},
{"metagrammar.dp:9:50","TemplateLoop",":","string",
{"metagrammar.dp:9:51","TemplateVariable","$f"},
{"metagrammar.dp:9:55","TemplateConst",":"},
{"metagrammar.dp:9:60","TemplateVariable","$line"},
{"metagrammar.dp:9:67","TemplateConst",":"},
{"metagrammar.dp:9:72","TemplateVariable","$col"}}}},
{"metagrammar.dp:12:1","Production","eof",
{"metagrammar.dp:12:7","Branch",
{"metagrammar.dp:12:7","Receipt",
{"metagrammar.dp:12:7","ElementLoop","!",
{"metagrammar.dp:12:7","Receipt",
{"metagrammar.dp:12:8","ElementAnyChar"}}}},
{"metagrammar.dp:12:13","TemplateConst",""}}},
{"metagrammar.dp:15:1","Production","white",
{"metagrammar.dp:15:9","Branch",
{"metagrammar.dp:15:9","Receipt",
{"metagrammar.dp:15:9","ElementClass"," \t\r\n"}},
{"metagrammar.dp:15:24","TemplateConst",""}},
{"metagrammar.dp:16:9","Branch",
{"metagrammar.dp:16:9","Receipt",
{"metagrammar.dp:16:9","ElementCall","comment"}},
{"metagrammar.dp:16:24","TemplateConst",""}}},
{"metagrammar.dp:19:1","Production","comment",
{"metagrammar.dp:19:11","Branch",
{"metagrammar.dp:19:11","Receipt",
{"metagrammar.dp:19:11","ElementString","#"},
{"metagrammar.dp:19:15","ElementLoop","*",
{"metagrammar.dp:19:15","Receipt",
{"metagrammar.dp:19:16","ElementLoop","!",
{"metagrammar.dp:19:16","Receipt",
{"metagrammar.dp:19:17","ElementString","\n"}}},
{"metagrammar.dp:19:22","ElementAnyChar","$c"}}},
{"metagrammar.dp:19:29","ElementString","\n"}},
{"metagrammar.dp:19:39","TemplateLoop",":","string",
{"metagrammar.dp:19:40","TemplateConst","#"},
{"metagrammar.dp:19:45","TemplateLoop","*","string",
{"metagrammar.dp:19:46","TemplateVariable","$c"}}}}},
{"metagrammar.dp:22:1","Production","ow",
{"metagrammar.dp:22:6","Branch",
{"metagrammar.dp:22:6","Receipt",
{"metagrammar.dp:22:6","ElementLoop","*",
{"metagrammar.dp:22:6","Receipt",
{"metagrammar.dp:22:7","ElementCall","white"}}}},
{"metagrammar.dp:22:24","TemplateConst",""}}},
{"metagrammar.dp:25:1","Production","production",
{"metagrammar.dp:25:14","Branch",
{"metagrammar.dp:25:14","Receipt",
{"metagrammar.dp:25:14","ElementCall","info","$i"},
{"metagrammar.dp:25:22","ElementCall","name","$n"},
{"metagrammar.dp:25:30","ElementCall","ow"},
{"metagrammar.dp:25:33","ElementString","="},
{"metagrammar.dp:25:37","ElementCall","branches","$bs"}},
{"metagrammar.dp:25:53","TemplateLoop",":","list",
{"metagrammar.dp:25:54","TemplateVariable","$i"},
{"metagrammar.dp:25:58","TemplateConst","Production"},
{"metagrammar.dp:25:72","TemplateVariable","$n"},
{"metagrammar.dp:25:76","TemplateVariable","$bs"}}}},
{"metagrammar.dp:28:1","Production","branch",
{"metagrammar.dp:28:11","Branch",
{"metagrammar.dp:28:11","Receipt",
{"metagrammar.dp:28:11","ElementCall","info","$i"},
{"metagrammar.dp:28:19","ElementCall","element_sequence","$es"},
{"metagrammar.dp:28:40","ElementString","->"},
{"metagrammar.dp:28:45","ElementCall","ow"},
{"metagrammar.dp:28:48","ElementCall","templ_element","$t"}},
{"metagrammar.dp:29:25","TemplateLoop",":","list",
{"metagrammar.dp:29:26","TemplateVariable","$i"},
{"metagrammar.dp:29:30","TemplateConst","Branch"},
{"metagrammar.dp:29:40","TemplateLoop",":","list",
{"metagrammar.dp:29:41","TemplateVariable","$i"},
{"metagrammar.dp:29:45","TemplateConst","Receipt"},
{"metagrammar.dp:29:56","TemplateVariable","$es"}},
{"metagrammar.dp:29:62","TemplateVariable","$t"}}}},
{"metagrammar.dp:32:1","Production","branches",
{"metagrammar.dp:32:12","Branch",
{"metagrammar.dp:32:12","Receipt",
{"metagrammar.dp:32:12","ElementCall","ow"},
{"metagrammar.dp:32:15","ElementLoop","!",
{"metagrammar.dp:32:15","Receipt",
{"metagrammar.dp:32:16","ElementCall","branch"}}}},
{"metagrammar.dp:32:58","TemplateLoop",":","sequence"}},
{"metagrammar.dp:33:12","Branch",
{"metagrammar.dp:33:12","Receipt",
{"metagrammar.dp:33:12","ElementCall","ow"},
{"metagrammar.dp:33:15","ElementCall","branch","$b"},
{"metagrammar.dp:33:25","ElementLoop","*",
{"metagrammar.dp:33:25","Receipt",
{"metagrammar.dp:33:26","ElementCall","ow"},
{"metagrammar.dp:33:29","ElementString","|"},
{"metagrammar.dp:33:33","ElementCall","ow"},
{"metagrammar.dp:33:36","ElementCall","branch","$bb"}}}},
{"metagrammar.dp:33:58","TemplateLoop",":","sequence",
{"metagrammar.dp:33:59","TemplateVariable","$b"},
{"metagrammar.dp:33:63","TemplateLoop","*","sequence",
{"metagrammar.dp:33:64","TemplateVariable","$bb"}}}}},
{"metagrammar.dp:36:1","Production","element",
{"metagrammar.dp:36:11","Branch",
{"metagrammar.dp:36:11","Receipt",
{"metagrammar.dp:36:11","ElementCall","info","$i"},
{"metagrammar.dp:36:19","ElementCall","name","$n"},
{"metagrammar.dp:36:27","ElementLoop","?",
{"metagrammar.dp:36:27","Receipt",
{"metagrammar.dp:36:28","ElementCall","ow"},
{"metagrammar.dp:36:31","ElementCall","var","$v"}}}},
{"metagrammar.dp:36:57","TemplateLoop",":","list",
{"metagrammar.dp:36:58","TemplateVariable","$i"},
{"metagrammar.dp:36:62","TemplateConst","ElementCall"},
{"metagrammar.dp:36:77","TemplateVariable","$n"},
{"metagrammar.dp:36:81","TemplateLoop","?","sequence",
{"metagrammar.dp:36:82","TemplateVariable","$v"}}}},
{"metagrammar.dp:37:11","Branch",
{"metagrammar.dp:37:11","Receipt",
{"metagrammar.dp:37:11","ElementCall","info","$i"},
{"metagrammar.dp:37:19","ElementCall","cstring","$s"},
{"metagrammar.dp:37:30","ElementLoop","?",
{"metagrammar.dp:37:30","Receipt",
{"metagrammar.dp:37:31","ElementCall","ow"},
{"metagrammar.dp:37:34","ElementCall","var","$v"}}}},
{"metagrammar.dp:37:57","TemplateLoop",":","list",
{"metagrammar.dp:37:58","TemplateVariable","$i"},
{"metagrammar.dp:37:62","TemplateConst","ElementString"},
{"metagrammar.dp:37:79","TemplateVariable","$s"},
{"metagrammar.dp:37:83","TemplateLoop","?","sequence",
{"metagrammar.dp:37:84","TemplateVariable","$v"}}}},
{"metagrammar.dp:38:11","Branch",
{"metagrammar.dp:38:11","Receipt",
{"metagrammar.dp:38:11","ElementCall","info","$i"},
{"metagrammar.dp:38:19","ElementString","("},
{"metagrammar.dp:38:23","ElementCall","element_sequence","$seq"},
{"metagrammar.dp:38:45","ElementString",")"},
{"metagrammar.dp:38:49","ElementCall","ow"},
{"metagrammar.dp:38:52","ElementCall","repet","$r"}},
{"metagrammar.dp:39:25","TemplateLoop",":","list",
{"metagrammar.dp:39:26","TemplateVariable","$i"},
{"metagrammar.dp:39:30","TemplateConst","ElementLoop"},
{"metagrammar.dp:39:45","TemplateVariable","$r"},
{"metagrammar.dp:40:33","TemplateLoop",":","list",
{"metagrammar.dp:40:34","TemplateVariable","$i"},
{"metagrammar.dp:40:38","TemplateConst","Receipt"},
{"metagrammar.dp:40:49","TemplateVariable","$seq"}}}},
{"metagrammar.dp:41:11","Branch",
{"metagrammar.dp:41:11","Receipt",
{"metagrammar.dp:41:11","ElementCall","info","$i"},
{"metagrammar.dp:41:19","ElementString","&"},
{"metagrammar.dp:41:23","ElementCall","ow"},
{"metagrammar.dp:41:26","ElementString","("},
{"metagrammar.dp:41:30","ElementCall","element_sequence","$seq"},
{"metagrammar.dp:41:52","ElementString",")"}},
{"metagrammar.dp:42:25","TemplateLoop",":","list",
{"metagrammar.dp:42:26","TemplateVariable","$i"},
{"metagrammar.dp:42:30","TemplateConst","ElementLoop"},
{"metagrammar.dp:42:45","TemplateConst","&"},
{"metagrammar.dp:43:33","TemplateLoop",":","list",
{"metagrammar.dp:43:34","TemplateVariable","$i"},
{"metagrammar.dp:43:38","TemplateConst","Receipt"},
{"metagrammar.dp:43:49","TemplateVariable","$seq"}}}},
{"metagrammar.dp:44:11","Branch",
{"metagrammar.dp:44:11","Receipt",
{"metagrammar.dp:44:11","ElementCall","info","$i"},
{"metagrammar.dp:44:19","ElementString","."},
{"metagrammar.dp:44:23","ElementLoop","?",
{"metagrammar.dp:44:23","Receipt",
{"metagrammar.dp:44:24","ElementCall","ow"},
{"metagrammar.dp:44:27","ElementCall","var","$v"}}}},
{"metagrammar.dp:44:57","TemplateLoop",":","list",
{"metagrammar.dp:44:58","TemplateVariable","$i"},
{"metagrammar.dp:44:62","TemplateConst","ElementAnyChar"},
{"metagrammar.dp:44:80","TemplateLoop","?","sequence",
{"metagrammar.dp:44:81","TemplateVariable","$v"}}}},
{"metagrammar.dp:45:11","Branch",
{"metagrammar.dp:45:11","Receipt",
{"metagrammar.dp:45:11","ElementCall","cclass","$c"}},
{"metagrammar.dp:45:57","TemplateVariable","$c"}},
{"metagrammar.dp:46:11","Branch",
{"metagrammar.dp:46:11","Receipt",
{"metagrammar.dp:46:11","ElementCall","info","$i"},
{"metagrammar.dp:46:19","ElementString","!"},
{"metagrammar.dp:46:23","ElementCall","ow"},
{"metagrammar.dp:46:26","ElementString","("},
{"metagrammar.dp:46:30","ElementCall","element_sequence","$seq"},
{"metagrammar.dp:46:52","ElementString",")"}},
{"metagrammar.dp:47:25","TemplateLoop",":","list",
{"metagrammar.dp:47:26","TemplateVariable","$i"},
{"metagrammar.dp:47:30","TemplateConst","ElementLoop"},
{"metagrammar.dp:47:45","TemplateConst","!"},
{"metagrammar.dp:48:33","TemplateLoop",":","list",
{"metagrammar.dp:48:34","TemplateVariable","$i"},
{"metagrammar.dp:48:38","TemplateConst","Receipt"},
{"metagrammar.dp:48:49","TemplateVariable","$seq"}}}},
{"metagrammar.dp:49:11","Branch",
{"metagrammar.dp:49:11","Receipt",
{"metagrammar.dp:49:11","ElementCall","info","$i"},
{"metagrammar.dp:49:19","ElementString","!"},
{"metagrammar.dp:49:23","ElementCall","ow"},
{"metagrammar.dp:49:26","ElementCall","element","$e"}},
{"metagrammar.dp:49:57","TemplateLoop",":","list",
{"metagrammar.dp:49:58","TemplateVariable","$i"},
{"metagrammar.dp:49:62","TemplateConst","ElementLoop"},
{"metagrammar.dp:49:77","TemplateConst","!"},
{"metagrammar.dp:49:82","TemplateLoop",":","list",
{"metagrammar.dp:49:83","TemplateVariable","$i"},
{"metagrammar.dp:49:87","TemplateConst","Receipt"},
{"metagrammar.dp:49:98","TemplateVariable","$e"}}}}},
{"metagrammar.dp:52:1","Production","repet",
{"metagrammar.dp:52:9","Branch",
{"metagrammar.dp:52:9","Receipt",
{"metagrammar.dp:52:9","ElementCall","rep","$r"}},
{"metagrammar.dp:52:21","TemplateVariable","$r"}},
{"metagrammar.dp:53:9","Branch",
{"metagrammar.dp:53:9","Receipt",
{"metagrammar.dp:53:9","ElementLoop","!",
{"metagrammar.dp:53:9","Receipt",
{"metagrammar.dp:53:10","ElementCall","rep"}}}},
{"metagrammar.dp:53:19","TemplateConst",":"}}},
{"metagrammar.dp:55:1","Production","element_sequence",
{"metagrammar.dp:55:20","Branch",
{"metagrammar.dp:55:20","Receipt",
{"metagrammar.dp:55:20","ElementLoop","*",
{"metagrammar.dp:55:20","Receipt",
{"metagrammar.dp:55:21","ElementCall","ow"},
{"metagrammar.dp:55:24","ElementCall","element","$e"}}},
{"metagrammar.dp:55:37","ElementCall","ow"}},
{"metagrammar.dp:55:45","TemplateLoop","*","sequence",
{"metagrammar.dp:55:46","TemplateVariable","$e"}}}},
{"metagrammar.dp:57:1","Production","cclchar",
{"metagrammar.dp:57:11","Branch",
{"metagrammar.dp:57:11","Receipt",
{"metagrammar.dp:57:11","ElementLoop","!",
{"metagrammar.dp:57:11","Receipt",
{"metagrammar.dp:57:12","ElementClass","[]\r\n\\"}}},
{"metagrammar.dp:57:25","ElementAnyChar","$c"}},
{"metagrammar.dp:57:35","TemplateVariable","$c"}},
{"metagrammar.dp:58:10","Branch",
{"metagrammar.dp:58:10","Receipt",
{"metagrammar.dp:58:10","ElementString","\\["}},
{"metagrammar.dp:58:35","TemplateConst","["}},
{"metagrammar.dp:59:10","Branch",
{"metagrammar.dp:59:10","Receipt",
{"metagrammar.dp:59:10","ElementString","\\]"}},
{"metagrammar.dp:59:35","TemplateConst","]"}},
{"metagrammar.dp:60:10","Branch",
{"metagrammar.dp:60:10","Receipt",
{"metagrammar.dp:60:10","ElementString","\\r"}},
{"metagrammar.dp:60:35","TemplateConst","\r"}},
{"metagrammar.dp:61:10","Branch",
{"metagrammar.dp:61:10","Receipt",
{"metagrammar.dp:61:10","ElementString","\\t"}},
{"metagrammar.dp:61:35","TemplateConst","\t"}},
{"metagrammar.dp:62:10","Branch",
{"metagrammar.dp:62:10","Receipt",
{"metagrammar.dp:62:10","ElementString","\\n"}},
{"metagrammar.dp:62:35","TemplateConst","\n"}},
{"metagrammar.dp:63:10","Branch",
{"metagrammar.dp:63:10","Receipt",
{"metagrammar.dp:63:10","ElementString","\\\\"}},
{"metagrammar.dp:63:35","TemplateConst","\\"}}},
{"metagrammar.dp:65:1","Production","cclass",
{"metagrammar.dp:65:10","Branch",
{"metagrammar.dp:65:10","Receipt",
{"metagrammar.dp:65:10","ElementCall","info","$i"},
{"metagrammar.dp:65:18","ElementString","["},
{"metagrammar.dp:65:22","ElementLoop","*",
{"metagrammar.dp:65:22","Receipt",
{"metagrammar.dp:65:23","ElementCall","cclchar","$c"}}},
{"metagrammar.dp:65:36","ElementString","]"},
{"metagrammar.dp:65:40","ElementLoop","?",
{"metagrammar.dp:65:40","Receipt",
{"metagrammar.dp:65:41","ElementCall","ow"},
{"metagrammar.dp:65:44","ElementCall","var","$v"}}}},
{"metagrammar.dp:66:17","TemplateLoop",":","list",
{"metagrammar.dp:66:18","TemplateVariable","$i"},
{"metagrammar.dp:66:22","TemplateConst","ElementClass"},
{"metagrammar.dp:66:38","TemplateLoop","*","string",
{"metagrammar.dp:66:39","TemplateVariable","$c"}},
{"metagrammar.dp:66:45","TemplateLoop","?","sequence",
{"metagrammar.dp:66:46","TemplateVariable","$v"}}}}},
{"metagrammar.dp:68:1","Production","name",
{"metagrammar.dp:68:8","Branch",
{"metagrammar.dp:68:8","Receipt",
{"metagrammar.dp:68:8","ElementLoop","?",
{"metagrammar.dp:68:8","Receipt",
{"metagrammar.dp:68:9","ElementString","::","$p"}}},
{"metagrammar.dp:68:19","ElementCall","letter","$a"},
{"metagrammar.dp:68:29","ElementLoop","*",
{"metagrammar.dp:68:29","Receipt",
{"metagrammar.dp:68:30","ElementCall","alnum","$b"}}}},
{"metagrammar.dp:68:49","TemplateLoop",":","string",
{"metagrammar.dp:68:50","TemplateLoop","?","string",
{"metagrammar.dp:68:51","TemplateVariable","$p"}},
{"metagrammar.dp:68:57","TemplateVariable","$a"},
{"metagrammar.dp:68:61","TemplateLoop","*","string",
{"metagrammar.dp:68:62","TemplateVariable","$b"}}}}},
{"metagrammar.dp:70:1","Production","var",
{"metagrammar.dp:70:7","Branch",
{"metagrammar.dp:70:7","Receipt",
{"metagrammar.dp:70:7","ElementString","$"},
{"metagrammar.dp:70:11","ElementCall","name","$n"}},
{"metagrammar.dp:70:38","TemplateLoop",":","string",
{"metagrammar.dp:70:39","TemplateConst","$"},
{"metagrammar.dp:70:44","TemplateVariable","$n"}}}},
{"metagrammar.dp:72:1","Production","letter",
{"metagrammar.dp:72:10","Branch",
{"metagrammar.dp:72:10","Receipt",
{"metagrammar.dp:72:10","ElementClass","abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_","$c"}},
{"metagrammar.dp:72:72","TemplateVariable","$c"}}},
{"metagrammar.dp:73:1","Production","digit",
{"metagrammar.dp:73:9","Branch",
{"metagrammar.dp:73:9","Receipt",
{"metagrammar.dp:73:9","ElementClass","0123456789","$c"}},
{"metagrammar.dp:73:28","TemplateVariable","$c"}}},
{"metagrammar.dp:75:1","Production","alnum",
{"metagrammar.dp:75:9","Branch",
{"metagrammar.dp:75:9","Receipt",
{"metagrammar.dp:75:9","ElementCall","letter","$c"}},
{"metagrammar.dp:75:22","TemplateVariable","$c"}},
{"metagrammar.dp:76:9","Branch",
{"metagrammar.dp:76:9","Receipt",
{"metagrammar.dp:76:9","ElementCall","digit","$c"}},
{"metagrammar.dp:76:21","TemplateVariable","$c"}}},
{"metagrammar.dp:78:1","Production","rep",
{"metagrammar.dp:78:7","Branch",
{"metagrammar.dp:78:7","Receipt",
{"metagrammar.dp:78:7","ElementClass","?+*","$c"}},
{"metagrammar.dp:78:19","TemplateVariable","$c"}}},
{"metagrammar.dp:80:1","Production","templ_element",
{"metagrammar.dp:80:17","Branch",
{"metagrammar.dp:80:17","Receipt",
{"metagrammar.dp:80:17","ElementCall","info","$i"},
{"metagrammar.dp:80:25","ElementCall","cstring","$s"}},
{"metagrammar.dp:80:39","TemplateLoop",":","list",
{"metagrammar.dp:80:40","TemplateVariable","$i"},
{"metagrammar.dp:80:44","TemplateConst","TemplateConst"},
{"metagrammar.dp:80:61","TemplateVariable","$s"}}},
{"metagrammar.dp:81:17","Branch",
{"metagrammar.dp:81:17","Receipt",
{"metagrammar.dp:81:17","ElementCall","info","$i"},
{"metagrammar.dp:81:25","ElementCall","var","$v"}},
{"metagrammar.dp:81:39","TemplateLoop",":","list",
{"metagrammar.dp:81:40","TemplateVariable","$i"},
{"metagrammar.dp:81:44","TemplateConst","TemplateVariable"},
{"metagrammar.dp:81:64","TemplateVariable","$v"}}},
{"metagrammar.dp:82:17","Branch",
{"metagrammar.dp:82:17","Receipt",
{"metagrammar.dp:82:17","ElementCall","info","$i"},
{"metagrammar.dp:82:25","ElementString","("},
{"metagrammar.dp:82:29","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:82:49","ElementCall","ow"},
{"metagrammar.dp:82:52","ElementString",")"},
{"metagrammar.dp:82:56","ElementCall","ow"},
{"metagrammar.dp:82:59","ElementCall","repet","$r"}},
{"metagrammar.dp:83:25","TemplateLoop",":","list",
{"metagrammar.dp:83:26","TemplateVariable","$i"},
{"metagrammar.dp:83:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:83:46","TemplateVariable","$r"},
{"metagrammar.dp:83:50","TemplateConst","string"},
{"metagrammar.dp:83:60","TemplateVariable","$seq"}}},
{"metagrammar.dp:84:17","Branch",
{"metagrammar.dp:84:17","Receipt",
{"metagrammar.dp:84:17","ElementCall","info","$i"},
{"metagrammar.dp:84:25","ElementString","{"},
{"metagrammar.dp:84:29","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:84:49","ElementCall","ow"},
{"metagrammar.dp:84:52","ElementString","}"},
{"metagrammar.dp:84:56","ElementCall","ow"},
{"metagrammar.dp:84:59","ElementCall","repet","$r"}},
{"metagrammar.dp:85:25","TemplateLoop",":","list",
{"metagrammar.dp:85:26","TemplateVariable","$i"},
{"metagrammar.dp:85:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:85:46","TemplateVariable","$r"},
{"metagrammar.dp:85:50","TemplateConst","sequence"},
{"metagrammar.dp:85:62","TemplateVariable","$seq"}}},
{"metagrammar.dp:86:17","Branch",
{"metagrammar.dp:86:17","Receipt",
{"metagrammar.dp:86:17","ElementCall","info","$i"},
{"metagrammar.dp:86:25","ElementString","["},
{"metagrammar.dp:86:29","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:86:49","ElementCall","ow"},
{"metagrammar.dp:86:52","ElementString","]"},
{"metagrammar.dp:86:56","ElementCall","ow"},
{"metagrammar.dp:86:59","ElementCall","repet","$r"}},
{"metagrammar.dp:87:25","TemplateLoop",":","list",
{"metagrammar.dp:87:26","TemplateVariable","$i"},
{"metagrammar.dp:87:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:87:46","TemplateVariable","$r"},
{"metagrammar.dp:87:50","TemplateConst","list"},
{"metagrammar.dp:87:58","TemplateVariable","$seq"}}},
{"metagrammar.dp:88:17","Branch",
{"metagrammar.dp:88:17","Receipt",
{"metagrammar.dp:88:17","ElementCall","info","$i"},
{"metagrammar.dp:88:25","ElementString","&"},
{"metagrammar.dp:88:29","ElementCall","ow"},
{"metagrammar.dp:88:32","ElementString","("},
{"metagrammar.dp:88:36","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:88:56","ElementCall","ow"},
{"metagrammar.dp:88:59","ElementString",")"}},
{"metagrammar.dp:89:25","TemplateLoop",":","list",
{"metagrammar.dp:89:26","TemplateVariable","$i"},
{"metagrammar.dp:89:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:89:46","TemplateConst","&"},
{"metagrammar.dp:89:51","TemplateConst","string"},
{"metagrammar.dp:89:61","TemplateVariable","$seq"}}},
{"metagrammar.dp:90:17","Branch",
{"metagrammar.dp:90:17","Receipt",
{"metagrammar.dp:90:17","ElementCall","info","$i"},
{"metagrammar.dp:90:25","ElementString","&"},
{"metagrammar.dp:90:29","ElementCall","ow"},
{"metagrammar.dp:90:32","ElementString","{"},
{"metagrammar.dp:90:36","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:90:56","ElementCall","ow"},
{"metagrammar.dp:90:59","ElementString","}"}},
{"metagrammar.dp:91:25","TemplateLoop",":","list",
{"metagrammar.dp:91:26","TemplateVariable","$i"},
{"metagrammar.dp:91:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:91:46","TemplateConst","&"},
{"metagrammar.dp:91:51","TemplateConst","sequence"},
{"metagrammar.dp:91:63","TemplateVariable","$seq"}}},
{"metagrammar.dp:92:17","Branch",
{"metagrammar.dp:92:17","Receipt",
{"metagrammar.dp:92:17","ElementCall","info","$i"},
{"metagrammar.dp:92:25","ElementString","&"},
{"metagrammar.dp:92:29","ElementCall","ow"},
{"metagrammar.dp:92:32","ElementString","["},
{"metagrammar.dp:92:36","ElementCall","templ_sequence","$seq"},
{"metagrammar.dp:92:56","ElementCall","ow"},
{"metagrammar.dp:92:59","ElementString","]"}},
{"metagrammar.dp:93:25","TemplateLoop",":","list",
{"metagrammar.dp:93:26","TemplateVariable","$i"},
{"metagrammar.dp:93:30","TemplateConst","TemplateLoop"},
{"metagrammar.dp:93:46","TemplateConst","&"},
{"metagrammar.dp:93:51","TemplateConst","list"},
{"metagrammar.dp:93:59","TemplateVariable","$seq"}}}},
{"metagrammar.dp:95:1","Production","templ_sequence",
{"metagrammar.dp:95:18","Branch",
{"metagrammar.dp:95:18","Receipt",
{"metagrammar.dp:95:18","ElementCall","ow"},
{"metagrammar.dp:95:21","ElementLoop","!",
{"metagrammar.dp:95:21","Receipt",
{"metagrammar.dp:95:22","ElementCall","templ_element"}}}},
{"metagrammar.dp:95:43","TemplateLoop",":","sequence"}},
{"metagrammar.dp:96:18","Branch",
{"metagrammar.dp:96:18","Receipt",
{"metagrammar.dp:96:18","ElementCall","ow"},
{"metagrammar.dp:96:22","ElementCall","templ_element","$e"},
{"metagrammar.dp:96:39","ElementLoop","*",
{"metagrammar.dp:96:39","Receipt",
{"metagrammar.dp:96:40","ElementCall","ow"},
{"metagrammar.dp:96:43","ElementString",","},
{"metagrammar.dp:96:47","ElementCall","ow"},
{"metagrammar.dp:96:50","ElementCall","templ_element","$ee"}}}},
{"metagrammar.dp:97:25","TemplateLoop",":","sequence",
{"metagrammar.dp:97:26","TemplateVariable","$e"},
{"metagrammar.dp:97:30","TemplateLoop","*","sequence",
{"metagrammar.dp:97:31","TemplateVariable","$ee"}}}}},
{"metagrammar.dp:99:1","Production","cstring",
{"metagrammar.dp:99:11","Branch",
{"metagrammar.dp:99:11","Receipt",
{"metagrammar.dp:99:11","ElementString","\""},
{"metagrammar.dp:99:16","ElementLoop","*",
{"metagrammar.dp:99:16","Receipt",
{"metagrammar.dp:99:17","ElementCall","cchar","$c"}}},
{"metagrammar.dp:99:28","ElementString","\""}},
{"metagrammar.dp:99:38","TemplateLoop","*","string",
{"metagrammar.dp:99:39","TemplateVariable","$c"}}}},
{"metagrammar.dp:101:1","Production","cchar",
{"metagrammar.dp:101:9","Branch",
{"metagrammar.dp:101:9","Receipt",
{"metagrammar.dp:101:9","ElementLoop","!",
{"metagrammar.dp:101:9","Receipt",
{"metagrammar.dp:101:10","ElementClass","\"\r\n\\"}}},
{"metagrammar.dp:101:20","ElementAnyChar","$c"}},
{"metagrammar.dp:101:35","TemplateVariable","$c"}},
{"metagrammar.dp:102:17","Branch",
{"metagrammar.dp:102:17","Receipt",
{"metagrammar.dp:102:17","ElementString","\\\""}},
{"metagrammar.dp:102:35","TemplateConst","\""}},
{"metagrammar.dp:103:17","Branch",
{"metagrammar.dp:103:17","Receipt",
{"metagrammar.dp:103:17","ElementString","\\r"}},
{"metagrammar.dp:103:35","TemplateConst","\r"}},
{"metagrammar.dp:104:17","Branch",
{"metagrammar.dp:104:17","Receipt",
{"metagrammar.dp:104:17","ElementString","\\t"}},
{"metagrammar.dp:104:35","TemplateConst","\t"}},
{"metagrammar.dp:105:17","Branch",
{"metagrammar.dp:105:17","Receipt",
{"metagrammar.dp:105:17","ElementString","\\n"}},
{"metagrammar.dp:105:35","TemplateConst","\n"}},
{"metagrammar.dp:106:17","Branch",
{"metagrammar.dp:106:17","Receipt",
{"metagrammar.dp:106:17","ElementString","\\\\"}},
{"metagrammar.dp:106:35","TemplateConst","\\"}}},
{"metagrammar.dp:109:1","Production","goal",
{"metagrammar.dp:109:8","Branch",
{"metagrammar.dp:109:8","Receipt",
{"metagrammar.dp:109:8","ElementCall","info","$i"},
{"metagrammar.dp:109:16","ElementLoop","+",
{"metagrammar.dp:109:16","Receipt",
{"metagrammar.dp:109:17","ElementCall","ow"},
{"metagrammar.dp:109:20","ElementCall","production","$ps"}}},
{"metagrammar.dp:109:37","ElementCall","ow"},
{"metagrammar.dp:109:40","ElementCall","eof"}},
{"metagrammar.dp:110:9","TemplateLoop",":","list",
{"metagrammar.dp:110:10","TemplateVariable","$i"},
{"metagrammar.dp:110:14","TemplateConst","Grammar"},
{"metagrammar.dp:110:25","TemplateLoop","+","sequence",
{"metagrammar.dp:110:26","TemplateVariable","$ps"}}}}}}
;

# Information retrieval (IR)
Information retrieval system.

1.	Work on a local document corpus.
2.	Parse and index documents using inverted file format
3.	Make use of stemming and stop lists.
4.	Implement matching based on tf-idf algorithm.
5.	Results are displayed based on relevance ranking.

## Directory
 - src/Source.cpp Program source codes
 - src/IndexCreator.ext Compiled, exectuable codes. Generate from source.cpp
 - data/stop.txt Stop words get from internet.
 - data/TD_IDF_INDEX.txt Web stite conetent get from Steves Institue site by web scrawler.
 - data/test/...  Different training results based on size. 

### Pseudo codes:

存数据
已知 term， doc， tf， idf
建一个hash mytable( key=term value=<vector>doc)
For 循环读取每行信息
If (tf!=0) 
Mytable[key]=vector.push(doc)
End for
返回mytable

查询 term
返回 mytable[term];

查询 term and term1  或者  term term1
返回 mytable[term] && mytable[term1]

查询 term or term1
返回 mytable[term] || mytable[term1]

查询 not term
返回 whole doc list - mytable[term]

用栈处理查询语句优先级
将处理后的查询语句循环查询



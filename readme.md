# FeedCat

Categorize RSS feeds.

- parse RSS feeds into articles
- query fulltext of an article if a provider specific implementation exists 


## implemented fulltext providers
- [n-tv](https://www.n-tv.de/incoming/RSS-Feeds-von-n-tv-de-article10735026.html)

## Requirements
| package                                              | req. package |
|------------------------------------------------------| --- |
| [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp/) | sqlite3 |

## Utility Requirements
| Script                                              | req. package |
| ------------------------------------------------------| --- |
| [dependency-graph](https://github.com/pvigier/dependency-graph)                               | graphviz |


## TODOs
- [ ] adaptive poll rate for known sources
- [ ] wrapper class for RSS urls allowing querying groups of urls
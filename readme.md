# FeedCat

Categorize RSS feeds.

- parse RSS feeds into articles
- query fulltext of an article if a provider specific implementation exists 


## implemented fulltext providers
- [n-tv](https://www.n-tv.de/software/RSS-Feeds-article6210.html)

## Requirements
| package                                              | req. package |
|------------------------------------------------------| --- |
| [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp/) | sqlite3 |


## TODOs
- [ ] adaptive poll rate for known sources
- [ ] wrapper class for RSS urls allowing querying groups of urls
# FeedCat

Categorize RSS feeds.

- parse RSS feeds into articles
- query fulltext of an article if a provider specific implementation exists 


## implemented (fulltext) providers
> **Legal Disclaimer**  
> Depending on your usecase copying, storing and publishing copyrighted material might be illegal. If you use these functions 
> I expect you're allowed to do so. I'm not responsible for any illegal use of this tool.
- [n-tv](https://www.n-tv.de/incoming/RSS-Feeds-von-n-tv-de-article10735026.html)

## Requirements
| package                                              | req. package |
|------------------------------------------------------| --- |
| [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp/) | sqlite3 |

## Utility Requirements
| Script                                              | req. package |
| ------------------------------------------------------| --- |
| [dependency-graph](https://github.com/pvigier/dependency-graph)                               | graphviz |


## Variation points
You can extend this project with the following variation points:

| What               | Description                                     | How                                                         |
|--------------------|-------------------------------------------------|-------------------------------------------------------------|
| Fulltext-Parser    | Parse article texts from your custom providers. | See `backend/network/FullTextParserStrategy.hpp`            |
| Article Properties | Store custom values in Articles.                | See [doc](/doc/source/markdown/tutorial_add_properties.md)  |                                          |
| DB-Interaction for custom Properties | Store custom values in a database. | See [doc](/doc/source/markdown/tutorial_add_properties.md)  |              
| DB-Endpoints | Use your own database.                          | See `backend/db/database_interface.hpp`                     |


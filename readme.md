# FeedCat

Store articles from RSS feeds and enrich them with custom information.

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


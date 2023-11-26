# FeedCat

Store articles from RSS feeds and enrich them with custom information.

## Requirements

following used projects have external dependencies. You might need to install them manually, 
check their readme for more information.

| package | When do I need this?                                  |
|-------------------------------|-------------------------------------------------------|
| [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp/) | if you want to use the MySQL DB-Controller.           |
| [dependency-graph](https://github.com/pvigier/dependency-graph) | if you want to visualize the architecture of feedcat. |


## Variation points
You can extend this project with the following variation points:

| What               | Description                                     | How                                                         |
|--------------------|-------------------------------------------------|-------------------------------------------------------------|
| Fulltext-Parser    | Parse article texts from your custom providers. | See `backend/network/FullTextParserStrategy.hpp`            |
| Article Properties | Store custom values in Articles.                | See [doc](/doc/source/markdown/tutorial_add_properties.md)  |                                          |
| DB-Interaction for custom Properties | Store custom values in a database. | See [doc](/doc/source/markdown/tutorial_add_properties.md)  |              
| DB-Endpoints | Use your own database.                          | See `backend/db/database_interface.hpp`                     |


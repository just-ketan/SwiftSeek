add_executable(swiftseek
    main.cpp

    # Core
    core/document/document_store.cpp
    core/inverted_index/inverted_index.cpp
    core/query/query_executor.cpp
    core/ranking/tfidf.cpp

    # Automata
    core/automata/aho_corasick.cpp

    # Bench / utils if needed later
)

target_include_directories(swiftseek PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


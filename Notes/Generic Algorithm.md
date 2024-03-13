# Notes:
- Try to use architecture Framer -> Searcher -> Transformer
- Framer has function getFrame(id). while is not -1, keep searching
- Searcher find a place or places to schedule the frame
- Tranformer just apply tranformation if possible. if not rollback changes
- Also we can wrap this architecture with a multirunner
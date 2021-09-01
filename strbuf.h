typedef struct {
    size_t length;
    size_t used;
    char *data;
} strbuf;

int sb_init(strbuf *, size_t);
void sb_destroy(strbuf *);
int sb_append(strbuf *, char);
int sb_remove(strbuf *, char *);
int sb_insert(strbuf *, int index, char item);
int sb_concat(strbuf *, char *);

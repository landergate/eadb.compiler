#include <script.h>

#define RE_PATH     "opt.db"
#define EA_PATH     "ea.db"
#define MAP_PATH    "res/athena_db.txt"

int main(int argc, char * argv[]) {
    int i = 0;
    int level = 0;
    char * script = NULL;
    script_t * context = NULL;

    if(script_init(&context, RE_PATH, EA_PATH, MAP_PATH, EATHENA))
        return 0;

    while(!item_iterate(context->db, &context->item)) {
        /* skip any script without statements */
        script = context->item.script;
        for (i = 0; script[i] != '\0'; i++) {
            /* comments can be problematic */
            if (script[i + 1] != '\0' && script[i] == '/' && script[i + 1] == '*') {
                level++;
            } else if (script[i] != '\0'  && script[i] == '*' && script[i + 1] == '/') {
                level--;
                i += 2;
            }
            if (!level && ';' == script[i])
                goto compile;
        }
        continue;

    compile:
        /* compile the item script */
        if (script_lexical(&context->token, context->item.script) ||
            script_analysis(context, &context->token, NULL, NULL) ||
            script_translate(context) ||
            script_generate(context) ||
            context->item.id == 0 ||
            script_block_free_all(context)) {
            goto failed;
        }
    }

clean:
    script_deit(&context);
    return 0;

failed:
    fprintf(stderr, "      script: %s\n", context->item.script);
    script_block_dump(context, stderr);
    goto clean;
}

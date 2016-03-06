#include <script.h>

#define RE_PATH     "resource.db"
#define RA_PATH     "rathena.db"
#define MAP_PATH    "db/athena_db.txt"

int main(int argc, char * argv[]) {
    script_t * context = NULL;

    if (script_init(&context, RE_PATH, RA_PATH, MAP_PATH, RATHENA))
        return 0;

    while(!item_iterate(context->db, &context->item)) {
        /* compile the item script */
        if(!script_check(context->item.script)) {
            if (script_lexical(&context->token, context->item.script) ||
                script_analysis(context, &context->token, NULL, NULL) ||
                script_translate(context) ||
                script_generate(context) ||
                context->item.id == 0) {
                /* dump the blocks
                fprintf(stderr, "[%d] script: %s\n", context->item.id, context->item.script);
                if(context->blocks != NULL)
                    script_block_dump(context, stderr);
                break;*/
            } else{
                printf("[%d]\n%s", context->item.id, context->buffer);
            }
        }

        script_block_free_all(context);
    }

    script_deit(&context);
    return 0;
}

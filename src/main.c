#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File size
size_t file_size(FILE *file) {
  if (!file) {
    return 0;
  }
  fpos_t original;
  if (fgetpos(file, &original) != 0) {
    printf("fgetpos() failed");
  }

  fseek(file, 0 , SEEK_END);
  long out = ftell(file);

  if (fsetpos(file, &original) != 0) {
    printf("fgetpos() failed");
  }
  return out;
}

// File contents (as heap allocated buffer)
char *file_contents(char *path) {
  FILE *file = fopen(path, "r");
  if (!file) {
    printf("Error opening file: %s\n", path);
    return NULL;
  }
  // Buffer for correct size + null terminator (for strings)
  long size = file_size(file);
  char *contents = malloc(size + 1);
  char *write_it = contents;

  size_t bytes_read = 0;
  size_t bytes_read_this_iteration = 0;

  while (bytes_read < size) {
    printf("Reading %ld bytes\n", size - bytes_read);
    // Read file into buffer
    size_t bytes_read_this_iteration = fread(write_it, 1, size - bytes_read, file);
    if (ferror(file)) {
      printf("Error reading file: %s\n", path);
      free(contents);
      return NULL;
    }

    bytes_read += bytes_read_this_iteration;
    write_it += bytes_read_this_iteration;

    if (feof(file)) {
      break;
    }
  }

  contents[bytes_read] = '\0';
  return contents;
}

void print_usage(char **argv) {
  printf("USAGE: %s <path_to_file_to_compile>\n", argv[0]);
}

typedef struct Error {
  enum ErrorType {
    ERROR_NONE = 0,
    ERROR_ARGUMENTS,
    ERROR_TYPE,
    ERROR_GENERIC,
    ERROR_SYNTAX,
    ERROR_TODO,
    // ERROR_FILE,
    ERROR_MAX
  } type;
  char *msg;
} Error;

Error ok = { ERROR_NONE, NULL };

void print_error(Error err) {
  if (err.type == ERROR_NONE) {
    return;
  }
  printf("ERROR: %s\n", err.msg);
  assert(ERROR_MAX == 6);
  switch (err.type) {
    default:
      printf("Unknown error type...");
      break;
    case ERROR_TODO:
      printf("TODO (not implemented)");
      break;
    case ERROR_SYNTAX:
      printf("Invalid syntax");
      break;
    case ERROR_TYPE:
      printf("Mismatched types");
      break;
    case ERROR_ARGUMENTS:
      printf("Invalid arguments");
      break;
    case ERROR_GENERIC:
      break;
    case ERROR_NONE:
      break;
  }
  putchar('\n');
  if (err.msg) {
    printf("Message: %s\n", err.msg);
  }
}

#define ERROR_CREATE(n, t, msg) Error (n) = { (t), (msg) };

#define ERROR_PREP(n, t, message) (n).type = (t), (n).msg = (message);

const char *whitespace = " \r\n";
const char *delimeters = " \r\n,():";

// Linked List
typedef struct Token {
  char *beginning;
  char *end;
  struct Token **next;
} Token;

// Lex the next token from the source and point beg and end to the start and end of the token
Error lex(char *source, Token *token) {
  Error err = ok;
  if (!source || !token) {
    ERROR_PREP(err, ERROR_ARGUMENTS, "Cannot lex NULL source");
    return err;
  };

  token->beginning = source;
  // Skip whitespace in the beginning
  token->beginning += strspn(token->beginning, whitespace);
  // printf("Skipped whitespace: \n");
  token->end = token->beginning;

  if (*token->end == '\0') {
    return err;
  }
  
  // Skip everything which is not in delimeters
  token->end += strcspn(token->beginning, delimeters);

  if (token->end == token->beginning) {
    token->end += 1;
  }

  return ok;
}

// TOOD: API to create new node
// -- API to add node as child
typedef long long integer_t;
typedef struct Node {
  enum NodeType {
    NODE_TYPE_NONE,
    NODE_TYPE_PROGRAM,
    NODE_TYPE_INTEGER,
    NODE_TYPE_MAX
  } type;

  union NodeValue {
    integer_t integer;
  } value;

  struct Node *children[3];
} Node;

// Functions returns boolean? Macro?
#define nonep(node) ((node).type == NODE_TYPE_NONE)
#define integerp(node) ((node).type == NODE_TYPE_INTEGER)

typedef struct Program {
  Node *root;
} Program;

// Todo: 
// - API to create a new bindin
// - API to add binding to env
typedef struct Binding {
  char *id;
  Node *value;
  struct Binding *next;
} Binding;

// Todo:
// - API to create a new environment
typedef struct Environment {
  struct Environment *parent;
  Binding *bind;
} Environment;


void environment_set() {

}

// int @return Zero upon success
int valid_identifier(char *id) {
  return strpbrk(id, delimeters) == NULL ? 1 : 0;
}

Error parse_expr(char *source, Node *result) {
  Token token;
  token.next = NULL;
  token.beginning = source;
  token.end = source;
  // char *beg = source;
  // char *end = source;
  Error err = ok;
  // While there is no error (we asign err to return value of lex
  // Then we get the type of error we asign to, and continue if it is none
  while((err = lex(token.end, &token)).type == ERROR_NONE) {
    if (token.end - token.beginning == 0) {
      break;
    }
    printf("Lexed: %.*s\n", (int)(token.end - token.beginning), token.beginning);
  };
  return err;
}

int main (int argc, char **argv) {

  if (argc < 2) {
    print_usage(argv);
    exit(0);
  }

  char *path = argv[1];
  char *contents = file_contents(path);
  if (contents) {
    // printf("Contents of %s:\n---\n\"%s\"\n---\n", path, contents);

    Node expression;
    Error err = parse_expr(contents, &expression);
    print_error(err);

    free(contents);
  }

  return 0;
}
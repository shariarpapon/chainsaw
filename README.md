## Chainsaw Tokenizer
By, Shariar Papon

<b>
---------------------------------------------
</b>

#### ** To use existing tokenizer import Chainsaw.dll **
#### ** For customization, entire visual studio solution is provided in the repo **

### Exported Contents
Here are the c++ methods and structures that are declared as exportable

```cpp
//This struct holds the data of a token type and the source string value of the token

struct CToken {
    int tokenId; //The token ID representing the respective GeneralTokenType enum value.
    char* tokenValue; //The raw string value of the token from the source.
    char* tokenStrRep; //A string representation of the token Id & value.
}
```

```cpp
//This function tokenizes the source char* passed in and returns an array of CToken pointers.
//Note the source char* must be null terminated to avoid undefined behavior.
//If keepCompact is true, nested scope blocks and expressions will not be expanded recursively.
//The size value is set to the number of CToken* in memory starting from the base of CToken**.

CToken** Tokenize(const char* source, bool keepCompact, int* size);
```

### Translate tokenId to general token types enum:
#### Enum Type Prefix Definitions:

 - seq: sequence starter
 - ind: indicator
 - enc: encapsulator
 - bks: block start
 - bke: block end
 - bk: block value (when in compact form, a minimized block is given this token type)
 - k: kills tokenizing process (either end of source string or unexpected character)

```cpp
enum GeneralTokenType {
	seq_delimiter = 0, //start at id = 0.
	seq_identifier,
	seq_number,
	seq_commentValue,

	ind_commentStart,
	ind_statementEnd,
	ind_operatorDelim,
	ind_accessor,

	enc_string,

	bks_scope,
	bke_scope,
	bk_scope,
	bks_expression,
	bke_expression,
	bk_expression,

	k_terminate,
	k_unexpected, //end at id = 16.
}
```

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "shared.h"
#include <map>
#include <string>
#include <vector>

class Preprocessor {
public:
  explicit Preprocessor();
  enum class ArgType {
    LABEL,
    REGISTER,
    // IMMEDIATE, // might be used later idk
    ADDRESS,
    NUMBER,
  };

  typedef struct arg {
    ArgType type;
    std::string contents;
  } arg_t;

  typedef struct inst {
    Opcode opcode;
    PseudoOpcode pseudoOpcode = PseudoOpcode::NONE;
    std::vector<arg_t *> arguments;
  } inst_t;

  typedef struct label_pos {
    uint16_t position;
    std::string label;
  } label_pos_t;

  void handle_new_label(char *text);
  void handle_opcode(char *text);
  void handle_label_mention(char *text);
  void handle_register(char *text);
  void handle_address(char *text);
  void handle_number(char *text);
  void handle_instruction();

  void build_intermediate_rom();
  void save_rom(std::string path);

private:
  inst_t *current_instruction = nullptr;
  std::string current_label = "(default)";
  std::map<std::string, std::vector<inst_t *>> labels;
  std::map<std::string, std::vector<uint8_t>> stage2_rom;
  std::map<std::string, std::vector<label_pos_t *>> stage2_rom_label_positions;
  std::vector<uint8_t> stage3_rom;
};

void handle_new_label(char *text);
void handle_opcode(char *text);
void handle_label_mention(char *text);
void handle_register(char *text);
void handle_address(char *text);
void handle_number(char *text);
void handle_instruction();

Preprocessor &get_preprocessor();

#endif // PREPROCESSOR_H

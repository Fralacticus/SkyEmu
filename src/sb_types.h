/*****************************************************************************
 *
 *   SkyBoy GB Emulator
 *
 *   Copyright (c) 2021 Skyler "Sky" Saleh
 *
 **/

#ifndef SB_TYPES_H 
#define SB_TYPES_H 1

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#ifdef __GNUC__
  #define FORCE_INLINE inline __attribute__((always_inline))
#else
  #define FORCE_INLINE inline
#endif

#define SB_FILE_PATH_SIZE 1024
#define MAX_CARTRIDGE_SIZE 8 * 1024 * 1024
#define MAX_CARTRIDGE_RAM 128 * 1024
#define SB_U16_LO(A) ((A)&0xff)
#define SB_U16_LO_SET(A,VAL) A = (((A)&0xff00)|(((int)(VAL))&0xff))
#define SB_U16_HI(A) ((A >> 8) & 0xff)
#define SB_U16_HI_SET(A,VAL) A = (((A)&0x00ff)|((((int)(VAL))&0xff)<<8))


// Extract bits from a bitfield
#define SB_BFE(VALUE, BITOFFSET, SIZE)                                         \
  (((VALUE) >> (BITOFFSET)) & ((1llu << (SIZE)) - 1))
#define SB_BIT_TEST(VALUE,BITOFFSET) ((VALUE)&(1u<<(BITOFFSET)))
#define SB_MODE_PAUSE 0
#define SB_MODE_RESET 1
#define SB_MODE_RUN 2
#define SB_MODE_STEP 3
#define SB_MODE_REWIND 4

#define SB_LCD_W 160
#define SB_LCD_H 144
#define SB_PPU_BG_COLOR_PALETTES 64
#define SB_PPU_SPRITE_COLOR_PALETTES 64
#define SB_VRAM_BANK_SIZE 8192
#define SB_VRAM_NUM_BANKS 2

#define SB_WRAM_BANK_SIZE 4096
#define SB_WRAM_NUM_BANKS 8

#define SB_GB 0 
#define SB_GBC 1 

#define SB_PANEL_CPU      0
#define SB_PANEL_TILEMAPS 1
#define SB_PANEL_TILEDATA 2
#define SB_PANEL_AUDIO    3
#define SB_PANEL_IO       4

//Should be power of 2 for perf, 8192 samples gives ~85ms maximal latency for 48kHz
#define SB_AUDIO_RING_BUFFER_SIZE (2048*8)

#define SYSTEM_UNKNOWN 0
#define SYSTEM_GB 1
#define SYSTEM_GBA 2
#define SYSTEM_NDS 3

typedef struct{
  bool up,down,left,right;
  bool a, b, start, select;
  bool l, r,x,y; 
  bool pen_down, screen_folded;
} sb_joy_t;
  
typedef struct{
  int16_t data[SB_AUDIO_RING_BUFFER_SIZE];
  uint32_t read_ptr;
  uint32_t write_ptr;
}sb_ring_buffer_t;
typedef struct {
  int run_mode;          // [0: Reset, 1: Pause, 2: Run, 3: Step ]
  int step_instructions; // Number of instructions to advance while stepping
  int step_frames; 
  int pc_breakpoint;     // PC to run until
  int panel_mode;
  bool rom_loaded;
  int system;            // Enum to emulated system Ex. SYSTEM_GB, SYSTEM_GBA
  sb_joy_t joy;
  int frame;
  bool render_frame;
  double avg_frame_time; 
  sb_ring_buffer_t audio_ring_buff;
  float audio_channel_output[6];
  float mix_l_volume, mix_r_volume;
  float master_volume;
  int cmd_line_arg_count;
  char** cmd_line_args;
  //Temporary storage for use by cores that persists across frames but not in save states
  //or rewind buffers
  uint8_t core_temp_storage[1024*1024];
  uint32_t frames_since_rewind_push;
} sb_emu_state_t;
typedef struct{
  uint32_t addr;
  const char * name;
  struct{
    uint8_t start;
    uint8_t size;
    const char* name; 
  } bits[32]; 
}mmio_reg_t; 
typedef struct {
  // Registers
  uint16_t af, bc, de, hl, sp, pc;
  bool interrupt_enable;
  bool deferred_interrupt_enable;
  bool wait_for_interrupt; 
  bool prefix_op;
  bool trigger_breakpoint; 
  int last_inter_f; 
} sb_gb_cpu_t;

typedef struct {
  uint8_t data[65536];
  uint8_t wram[SB_WRAM_NUM_BANKS*SB_WRAM_BANK_SIZE];
} sb_gb_mem_t;

typedef struct {
  uint8_t data[MAX_CARTRIDGE_SIZE];
  uint8_t ram_data[MAX_CARTRIDGE_RAM]; 
  char title[17];
  char save_file_path[SB_FILE_PATH_SIZE]; 
  bool game_boy_color;
  bool ram_write_enable;
  bool ram_is_dirty; 
  uint8_t type;
  uint8_t mbc_type; 
  uint8_t mapped_ram_bank;
  unsigned mapped_rom_bank;
  int rom_size;
  int ram_size;
} sb_gb_cartridge_t;

typedef struct{
  unsigned int scanline_cycles;
  unsigned int curr_scanline;
  unsigned int curr_window_scanline;
  uint8_t *framebuffer;
  uint8_t vram[SB_VRAM_BANK_SIZE*SB_VRAM_NUM_BANKS];
  uint8_t color_palettes[SB_PPU_BG_COLOR_PALETTES+SB_PPU_SPRITE_COLOR_PALETTES];
  bool in_hblank; //Used for HDMA
  bool wy_eq_ly;
  bool last_frame_ppu_disabled;
} sb_lcd_ppu_t;
typedef struct{
  bool in_hblank; 
  bool active;
  int bytes_transferred;

  bool oam_dma_active;
  int oam_bytes_transferred; 
} sb_dma_t;

typedef struct{
  int clocks_till_div_inc;
  int clocks_till_tima_inc;
} sb_timer_t;

static FORCE_INLINE uint32_t sb_ring_buffer_size(sb_ring_buffer_t* buff){
  if(buff->read_ptr>SB_AUDIO_RING_BUFFER_SIZE){
    buff->write_ptr-=SB_AUDIO_RING_BUFFER_SIZE;
    buff->read_ptr-=SB_AUDIO_RING_BUFFER_SIZE;
  }
  uint32_t v = (buff->write_ptr-buff->read_ptr);
  v= v%SB_AUDIO_RING_BUFFER_SIZE;
  return v;
}
typedef struct {
  sb_gb_cartridge_t cart;
  sb_gb_cpu_t cpu;
  sb_gb_mem_t mem;
  sb_lcd_ppu_t lcd;
  sb_timer_t timers;
  sb_dma_t dma; 
  int model; 
} sb_gb_t;  

typedef void (*sb_opcode_impl_t)(sb_gb_t*,int op1,int op2, int op1_enum, int op2_enum, const uint8_t * flag_mask);

static inline float sb_random_float(float min, float max){
  float v = rand()/(float)RAND_MAX;
  return min + v*(max-min);
}
static inline bool sb_path_has_file_ext(const char * path, const char * ext){
  int ext_len = strlen(ext);
  int path_len = strlen(path);
  if(path_len<ext_len)return false;
  for(int i=0;i<ext_len;++i){
    if(tolower(path[path_len-ext_len+i])!=tolower(ext[i]))return false;
  }
  return true;
}
static uint8_t* sb_load_file_data(const char* path, size_t *file_size){
  FILE *f = fopen(path, "rb");
  if(file_size)*file_size = 0; 
  if(f){
    size_t size = 0; 
    fseek(f, 0,SEEK_END);
    size = ftell(f);
    fseek(f, 0,SEEK_SET);
    uint8_t *data = (uint8_t*)malloc(size);
    if(!data)return NULL;
    size =fread(data, 1, size, f);
    if(size==EOF){size = 0; free(data);} 
    if(file_size)*file_size = size;
    printf("Loaded file %s file_size %zu\n",path,*file_size);
    return data;
  }else{
    printf("Failed to open file %s\n",path);
  }
  return NULL;

}
static bool sb_save_file_data(const char* path, uint8_t* data, size_t file_size){
  FILE *f = fopen(path, "wb");
  size_t written = -1; 
  if(f){
    written = fwrite(data,1,file_size, f);
  }
  if(written!=file_size){
    printf("Error failed to save: %s (wrote: %zu out of %zu)\n",path,written,file_size);
  }else{
    printf("Saved: %s (size: %zu)\n",path,written);

  }
  return written ==file_size;
}
static void sb_free_file_data(uint8_t* data){
  if(data)free(data);
}
static void sb_breakup_path(const char* path, const char** base_path, const char** file_name, const char** ext){
  static char tmp_path[4096];
  strncpy(tmp_path,path,4096-1);
  tmp_path[4095]='\0';
  size_t sz = strlen(tmp_path);
  *base_path = "";
  *file_name = tmp_path;
  *ext = ""; 
  // Search for end of extension or start of base path
  bool found_ext = false;
  while(sz--){
    if(tmp_path[sz]=='.'&&!found_ext){
      tmp_path[sz] = '\0';
      found_ext = true;
      *ext = tmp_path + sz+1;
      *file_name = tmp_path;
    }
    if(tmp_path[sz]=='\\'||tmp_path[sz]=='/'){
      tmp_path[sz]='\0';
      *file_name = tmp_path+sz+1; 
      *base_path = tmp_path;
      break; 
    }
  }
}
static bool se_load_bios_file(const char* name, const char* base_path, const char* file_name, uint8_t * data, size_t data_size){
  bool loaded_bios=false;
  const char* base, *file, *ext; 
  sb_breakup_path(base_path, &base,&file, &ext);
  static char bios_path[SB_FILE_PATH_SIZE];
  snprintf(bios_path,SB_FILE_PATH_SIZE,"%s/%s",base, file_name);
  bios_path[SB_FILE_PATH_SIZE-1]=0;
  size_t bios_bytes=0;
  uint8_t *bios_data = sb_load_file_data(bios_path, &bios_bytes);
  if(bios_data){
    if(bios_bytes==data_size){
      printf("Loaded %s from %s\n",name, bios_path);
      memcpy(data,bios_data,data_size);
      loaded_bios=true;
    }else{
      printf("%s file at %s is incorrectly sized. Expected %zu bytes, got %zu bytes",name,file_name,data_size,bios_bytes);
    }
  }
  free(bios_data);
  return loaded_bios;
}
static FILE * se_load_log_file(const char* rom_path, const char* log_name){
  bool loaded_bios=false;
  const char* base, *file, *ext; 
  sb_breakup_path(rom_path, &base,&file, &ext);
  static char log_path[SB_FILE_PATH_SIZE];
  snprintf(log_path,SB_FILE_PATH_SIZE,"%s/%s.%s",base, file,log_name);
  log_path[SB_FILE_PATH_SIZE-1]=0;
  FILE * f = fopen(log_path, "rb");
  if(f)printf("Loaded log file:%s\n",log_path);
  return f; 
}
#endif

/* @file hash_map.h
 *
 */

typedef struct hash_bucket {
    struct hash_bucket* next;
    uint64_t key;
    uint64_t val;
} hash_bucket;

typedef struct hash_map {
    hash_bucket** buckets;
    int num_buckets;
} hash_map;

uint64_t _hash_function(hash_map* map, uint64_t key) {
    return (key % map->num_buckets);
}

hash_map* _hash_map_create(int num_buckets) {
    hash_map* map = (hash_map*) malloc(sizeof(hash_map));

    if( map ) {
      map->num_buckets = num_buckets; 
      map->buckets = (hash_bucket**) malloc(sizeof(hash_bucket*) * num_buckets);

       if( !map->buckets ) {
         free(map);
         return NULL;
       }

       for(int i = 0; i < num_buckets; ++i) 
         map->buckets[i] = NULL;
    }

    return map; 
}

void _hash_map_destroy(hash_map* map) {
  //not implemented 
}

hash_bucket* _hash_map_lookup(hash_map* map, uint64_t key) {
    uint64_t hash = _hash_function(map, key);

    if(map->buckets[hash] == NULL) {
      return NULL; 
    } else {
      hash_bucket* cur = map->buckets[hash];
      
      while(cur->key != key && cur->next)
        cur = cur->next;
    
      return cur;
    }
}

bool _hash_map_insert(hash_map* map, uint64_t key, uint64_t val) {
    uint64_t hash = _hash_function(map, key);

    hash_bucket* bucket = (hash_bucket*) malloc(sizeof(hash_bucket));
      
    if(!bucket)
      return false;

    bucket->next = NULL;
    bucket->key = key;
    bucket->val = val;

    if(map->buckets[hash] == NULL) {
      map->buckets[hash] = bucket;
    } else {
      hash_bucket* cur = map->buckets[hash];
      while(cur->next) {
        cur = cur->next;
      }

      cur->next = bucket; 
    }

    return true;
}

